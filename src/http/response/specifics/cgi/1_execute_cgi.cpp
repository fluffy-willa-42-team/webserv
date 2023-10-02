#include "response.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void free_exec_cgi(const Env& env, char * const *env_cast, int pipe_fd[2]){
	freeCopy(env, env_cast);
	if (pipe_fd[0] >= 0){
		close(pipe_fd[0]);
	}
	if (pipe_fd[1] >= 0){
		close(pipe_fd[1]);
	}
}

string read_buff_cgi(int fd, e_status& r_status){
	static char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	int32_t length_read = read(fd, buffer, BUFFER_SIZE);
	if (length_read < 0){
		r_status = S_ERROR;
		DEBUG_WARN_ << "Failed to read from CGI response: " << errno << endl;
		return "";
	}
	else if (length_read != BUFFER_SIZE){
		r_status = S_STOP;
	}
	else {
		r_status = S_CONTINUE;
	}
	return string(buffer, length_read);
}

e_status exec_cgi(const Env& env, const string& cgi_bin, const string& file, string& response){
	int pipe_fd[2] = {-1, -1};
	char * const argv[3] = {
		(char *const) cgi_bin.c_str(),
		(char *const) file.c_str(),
		NULL
	};
	char * const *env_cast = createCopy(env);

	if (!env_cast){
		free_exec_cgi(env, env_cast, pipe_fd);
		DEBUG_ERROR_ << "CGI: Could not create envirement variable" << endl;
		return S_ERROR;
	}

	if (pipe(pipe_fd) < 0){
		free_exec_cgi(env, env_cast, pipe_fd);
		DEBUG_ERROR_ << "CGI: Could not create a pipe" << endl;
		return S_ERROR;
	}

	pid_t pid = fork();
	if (pid < 0){
		free_exec_cgi(env, env_cast, pipe_fd);
		DEBUG_ERROR_ << "CGI: Could not Fork" << endl;
		return S_ERROR;
	}
	else if (pid == 0){
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0){
			free_exec_cgi(env, env_cast, pipe_fd);
			exit(EXIT_FAILURE);
		}

		execve(argv[0], argv, env_cast);

		free_exec_cgi(env, env_cast, pipe_fd);
		exit(EXIT_FAILURE);
	}
	else {
		int child_status = 0;
		waitpid(pid, &child_status, 0);

		int flags = fcntl(pipe_fd[0], F_GETFL, 0);
		if (flags == -1) {
			DEBUG_ERROR_ << "CGI: Could not get flag for pipe" << endl;
			return S_ERROR;
		}

		if (fcntl(pipe_fd[0], F_SETFL, flags | O_NONBLOCK) == -1) {
			DEBUG_ERROR_ << "CGI: Could not set flag for pipe" << endl;
			return S_ERROR;
		}
		
		if (!WIFEXITED(child_status)){
			free_exec_cgi(env, env_cast, pipe_fd);
			DEBUG_ERROR_ << "CGI: Did not execute properly" << endl;
			return S_ERROR;
		}

		e_status r_status = S_CONTINUE;
		while (r_status == S_CONTINUE){
			response += read_buff_cgi(pipe_fd[0], r_status);
			if (r_status == S_ERROR){
				free_exec_cgi(env, env_cast, pipe_fd);
				DEBUG_ERROR_ << "CGI: Could not Read" << endl;
				return S_ERROR;
			}
		}

		DEBUG_ << "CGI response: " << endl << BLUE << response << RESET << endl;
		
		free_exec_cgi(env, env_cast, pipe_fd);
		return S_CONTINUE;
	}
}