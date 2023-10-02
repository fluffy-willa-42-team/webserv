#include "response.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_pipe {
	int read;
	int write;
}	t_pipe;

void free_exec_cgi(const Env& env, char * const *env_cast, t_pipe pipe1, t_pipe pipe2){
	freeCopy(env, env_cast);
	if (pipe1.read >= 0){
		close(pipe1.read);
	}
	if (pipe1.write >= 0){
		close(pipe1.write);
	}
	if (pipe2.read >= 0){
		close(pipe2.read);
	}
	if (pipe2.write >= 0){
		close(pipe2.write);
	}
}

string read_buff_cgi(int fd, e_status& r_status){
	static char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	int32_t length_read = read(fd, buffer, BUFFER_SIZE);
	if (length_read < 0){
		r_status = S_STOP;
		// DEBUG_WARN_ << "Failed to read from CGI response: " << errno << endl;
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

e_status exec_cgi(
	const Env& env,
	const string& cgi_bin,
	const string& req_body,
	const string& file,
	string& response
){
	t_pipe pipe1 = {-1, -1};
	t_pipe pipe2 = {-1, -1};
	char * const argv[3] = {
		const_cast<char*>(cgi_bin.c_str()),
		const_cast<char*>(file.c_str()),
		NULL
	};
	char * const *env_cast = createCopy(env);

	if (!env_cast){
		free_exec_cgi(env, env_cast, pipe1, pipe2);
		DEBUG_ERROR_ << "CGI: Could not create envirement variable" << endl;
		return S_ERROR;
	}

	if (pipe((int *) &pipe1) < 0){
		free_exec_cgi(env, env_cast, pipe1, pipe2);
		DEBUG_ERROR_ << "CGI: Could not create a pipe" << endl;
		return S_ERROR;
	}
	if (!req_body.empty()){
		if (pipe((int *) &pipe2) < 0){
			free_exec_cgi(env, env_cast, pipe1, pipe2);
			DEBUG_ERROR_ << "CGI: Could not create a pipe" << endl;
			return S_ERROR;
		}
	}

	pid_t pid = fork();
	if (pid < 0){
		free_exec_cgi(env, env_cast, pipe1, pipe2);
		DEBUG_ERROR_ << "CGI: Could not Fork" << endl;
		return S_ERROR;
	}
	else if (pid == 0){
		if (!req_body.empty()){
			//  save STDOUT
			int fd_write = dup(STDOUT_FILENO);

			//  pipe2.write => STDOUT
			if (dup2(pipe2.write, STDOUT_FILENO) < 0){
				free_exec_cgi(env, env_cast, pipe1, pipe2);
				exit(EXIT_FAILURE);
			}

			//  pipe2.read => STDIN
			if (dup2(pipe2.read, STDIN_FILENO) < 0){
				free_exec_cgi(env, env_cast, pipe1, pipe2);
				exit(EXIT_FAILURE);
			}

			cout << req_body;

			//  STDOUT Copy => STDOUT
			if (dup2(fd_write, STDOUT_FILENO) < 0){
				free_exec_cgi(env, env_cast, pipe1, pipe2);
				exit(EXIT_FAILURE);
			}
		}
		if (dup2(pipe1.write, STDOUT_FILENO) < 0){
			free_exec_cgi(env, env_cast, pipe1, pipe2);
			exit(EXIT_FAILURE);
		}

		execve(argv[0], argv, env_cast);

		free_exec_cgi(env, env_cast, pipe1, pipe2);
		exit(EXIT_FAILURE);
	}
	else {
		int child_status = 0;
		waitpid(pid, &child_status, 0);

		int flags = fcntl(pipe1.read, F_GETFL, 0);
		if (flags == -1) {
			DEBUG_ERROR_ << "CGI: Could not get flag for pipe" << endl;
			return S_ERROR;
		}

		if (fcntl(pipe1.read, F_SETFL, flags | O_NONBLOCK) == -1) {
			DEBUG_ERROR_ << "CGI: Could not set flag for pipe" << endl;
			return S_ERROR;
		}
		
		if (!WIFEXITED(child_status)){
			free_exec_cgi(env, env_cast, pipe1, pipe2);
			DEBUG_ERROR_ << "CGI: Did not execute properly" << endl;
			return S_ERROR;
		}

		e_status r_status = S_CONTINUE;
		while (r_status == S_CONTINUE){
			response += read_buff_cgi(pipe1.read, r_status);
			if (r_status == S_ERROR){
				free_exec_cgi(env, env_cast, pipe1, pipe2);
				DEBUG_ERROR_ << "CGI: Could not Read" << endl;
				return S_ERROR;
			}
		}

		DEBUG_ << "CGI response: " << endl << BLUE << response << RESET << endl;
		
		free_exec_cgi(env, env_cast, pipe1, pipe2);
		return S_CONTINUE;
	}
}