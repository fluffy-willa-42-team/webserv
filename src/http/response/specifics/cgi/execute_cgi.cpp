#include "response.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void free_exec_cgi(const Env& env, char * const *env_cast, int pipe_fd[2]);
string read_buff_cgi(int fd, e_status& r_status);

string exec_cgi(const Env& env, const string& cgi_bin, const string& file){
	int pipe_fd[2] = {-1, -1};
	char * const argv[3] = {
		(char *const) cgi_bin.c_str(),
		(char *const) file.c_str(),
		NULL
	};
	char * const *env_cast = createCopy(env);

	if (!env_cast){
		free_exec_cgi(env, env_cast, pipe_fd);
		throw runtime_error("Env allocation failure");
	}

	if (pipe(pipe_fd) < 0){
		free_exec_cgi(env, env_cast, pipe_fd);
		throw runtime_error("Pipe allocation failure");
	}

	cout << pipe_fd[0] << " | " << pipe_fd[1] << endl;

	pid_t pid = fork();
	if (pid < 0){
		free_exec_cgi(env, env_cast, pipe_fd);
		throw runtime_error("Failure to fork");
	}
	else if (pid == 0){
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0){
			DEBUG_WARN_ << "Du2 fail" << endl;
			free_exec_cgi(env, env_cast, pipe_fd);
			exit(EXIT_FAILURE);
		}

		execve(argv[0], argv, env_cast);

		// DEBUG_WARN_ << "execve fail" << endl;

		free_exec_cgi(env, env_cast, pipe_fd);
		exit(EXIT_FAILURE);
	}
	else {
		int status = 0;
		waitpid(pid, &status, 0);

		int flags = fcntl(pipe_fd[0], F_GETFL, 0);
		if (flags == -1) {
			perror("fcntl");
			throw runtime_error("Failed to execute");
		}

		if (fcntl(pipe_fd[0], F_SETFL, flags | O_NONBLOCK) == -1) {
			perror("fcntl");
			throw runtime_error("Failed to execute");
		}
		
		if (!WIFEXITED(status)){
			free_exec_cgi(env, env_cast, pipe_fd);
			throw runtime_error("Failed to execute");
		}

		DEBUG_INFO_ << "TEST1" << endl;

		string test;
		e_status r_status = S_CONTINUE;
		while (r_status == S_CONTINUE){
			test += read_buff_cgi(pipe_fd[0], r_status);
			if (r_status == S_ERROR){
				free_exec_cgi(env, env_cast, pipe_fd);
				throw runtime_error("Could not Read");
			}
		}

		DEBUG_ << test << endl;
		
		free_exec_cgi(env, env_cast, pipe_fd);
		return test;
	}
}