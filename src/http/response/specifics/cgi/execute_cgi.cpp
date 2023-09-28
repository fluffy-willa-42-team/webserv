#include "response.hpp"
#include <unistd.h>
#include <sys/wait.h>

void exit_exec_cgi(const Env& env, char * const *env_cast, int pipe_fd[2]){
	freeCopy(env, env_cast);
	if (pipe_fd[0] >= 0){
		close(pipe_fd[0]);
	}
	if (pipe_fd[1] >= 0){
		close(pipe_fd[1]);
	}
	
}

void exec_child(char *const *argv, char *const *env, int pipe_fd[2]){
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0){
		return ;
	}

	execve(argv[0], argv, env);

	DEBUG_WARN_ << "execve fail" << endl;
	perror("execve");

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(1);
}

string exec_cgi(const Env& env, const string& cgi_bin, const string& file){
	char * const *env_cast = createCopy(env);
	char * const argv[3] = {
		(char *const) cgi_bin.c_str(),
		(char *const) file.c_str(),
		NULL
	};

	int pipe_fd[2] = {-1, -1};
	if (pipe(pipe_fd) < 0){
		cout << "xx" << endl;
		exit_exec_cgi(env, env_cast, pipe_fd);
		throw runtime_error("Pipe allocation failure");
	}

	cout << pipe_fd[0] << " | " << pipe_fd[1] << endl;

	pid_t pid = fork();
	if (pid < 0){
		cout << "xxx" << endl;
		exit_exec_cgi(env, env_cast, pipe_fd);
		throw runtime_error("Failure to fork");
	}
	else if (pid == 0){
		exec_child(argv, env_cast, pipe_fd);
		exit_exec_cgi(env, env_cast, pipe_fd);
		exit(0);
	}

	int status = 0;
	waitpid(pid, &status, 0);
	
	if (WEXITSTATUS(status) != 0){
		exit_exec_cgi(env, env_cast, pipe_fd);
		throw runtime_error("Failed to execute");
	}

	char buffer[BUFFER_SIZE];

	ssize_t char_read = read(pipe_fd[1], buffer, BUFFER_SIZE);

	if (char_read < 0){
		perror("test");
		exit_exec_cgi(env, env_cast, pipe_fd);
		throw runtime_error("xxxx");
	}
	cout << YELLOW << char_read << " | " << RESET << endl;

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	freeCopy(env, env_cast);
	return "OK";
}