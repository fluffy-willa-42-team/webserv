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
	t_pipe pipe_out = {-1, -1};
	t_pipe pipe_in = {-1, -1};
	char * const argv[3] = {
		const_cast<char*>(cgi_bin.c_str()),
		const_cast<char*>(file.c_str()),
		NULL
	};
	char * const *env_cast = createCopy(env);

	if (!env_cast){
		free_exec_cgi(env, env_cast, pipe_out, pipe_in);
		DEBUG_ERROR_ << "CGI: Could not create envirement variable" << endl;
		return S_ERROR;
	}

	if (pipe((int *) &pipe_out) < 0){
		free_exec_cgi(env, env_cast, pipe_out, pipe_in);
		DEBUG_ERROR_ << "CGI: Could not create a pipe" << endl;
		return S_ERROR;
	}
	if (pipe((int *) &pipe_in) < 0){
		free_exec_cgi(env, env_cast, pipe_out, pipe_in);
		DEBUG_ERROR_ << "CGI: Could not create a pipe" << endl;
		return S_ERROR;
	}

	pid_t pid = fork();
	if (pid < 0){
		free_exec_cgi(env, env_cast, pipe_out, pipe_in);
		DEBUG_ERROR_ << "CGI: Could not Fork" << endl;
		return S_ERROR;
	}
	else if (pid == 0){
		if (dup2(pipe_in.read, STDIN_FILENO) < 0){
			free_exec_cgi(env, env_cast, pipe_out, pipe_in);
			exit(EXIT_FAILURE);
		}
		if (dup2(pipe_out.write, STDOUT_FILENO) < 0){
			free_exec_cgi(env, env_cast, pipe_out, pipe_in);
			exit(EXIT_FAILURE);
		}

		close(pipe_in.write);
		close(pipe_out.read);

		DEBUG_ERROR_ << "execve" << endl;
		execve(argv[0], argv, env_cast);
		DEBUG_ERROR_ << "Failed execve" << endl;

		close(pipe_out.write);
		close(pipe_in.read);

		free_exec_cgi(env, env_cast, pipe_out, pipe_in);
		exit(EXIT_FAILURE);
	}
	else {
		if (!req_body.empty()){
			DEBUG_ERROR_ << "Has Body: " << req_body.size() << " | " << endl;
			ssize_t write_c = write(pipe_in.write, req_body.c_str(), req_body.size());
			if (write_c == -1){
				DEBUG_ERROR_ << "CGI write fail " << strerror(errno) << endl;
				exit(EXIT_FAILURE);
			}
			DEBUG_ERROR_ << "Has Body: " << req_body.size() << endl;
		}
		else {
			DEBUG_ERROR_ << "Has No Body" << endl;
			ssize_t write_c = write(pipe_in.write, "\0", 1);
			if (write_c == -1){
				DEBUG_ERROR_ << "CGI write fail " << strerror(errno) << endl;
				exit(EXIT_FAILURE);
			}
		}

		DEBUG_ERROR_ << "execve ee" << endl;
		
		close(pipe_in.read);
		close(pipe_in.write);
		close(pipe_out.write);

		int child_status = 0;
		waitpid(pid, &child_status, 0);

		DEBUG_ERROR_ << "End execve" << endl;

		if (!WIFEXITED(child_status)){
			free_exec_cgi(env, env_cast, pipe_out, pipe_in);
			DEBUG_ERROR_ << "CGI: Did not execute properly" << endl;
			return S_ERROR;
		}

		e_status r_status = S_CONTINUE;
		while (r_status == S_CONTINUE){
			response += read_buff_cgi(pipe_out.read, r_status);
			if (r_status == S_ERROR){
				free_exec_cgi(env, env_cast, pipe_out, pipe_in);
				DEBUG_ERROR_ << "CGI: Could not Read" << endl;
				return S_ERROR;
			}
		}

		DEBUG_ << "CGI response: " << endl << BLUE << response << RESET << endl;
		
		free_exec_cgi(env, env_cast, pipe_out, pipe_in);
		return S_CONTINUE;
	}
}