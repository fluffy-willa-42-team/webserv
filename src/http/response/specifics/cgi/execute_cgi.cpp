#include "response.hpp"
#include <unistd.h>
#include <sys/wait.h>

void exec_child(char *const *argv, char *const *env, int pipe_fd[2]){
	if (dup2(pipe_fd[0], STDOUT_FILENO) < 0){
		return ;
	}
	if (dup2(pipe_fd[1], STDIN_FILENO) < 0){
		return ;
	}

	execve(argv[1], argv, env);

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(0);
}

void exit_exec_cgi(const Env& env, char * const *env_cast, int pipe_fd[2], const string& message){
	freeCopy(env, env_cast);
	if (pipe_fd[0] >= 0){
		close(pipe_fd[0]);
	}
	if (pipe_fd[1] >= 0){
		close(pipe_fd[1]);
	}
	throw runtime_error(message);
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
		exit_exec_cgi(env, env_cast, pipe_fd, "Pipe allocation failure");
	}

	cout << pipe_fd[0] << " | " << pipe_fd[1] << endl;

	pid_t pid = fork();
	if (pid < 0){
		exit_exec_cgi(env, env_cast, pipe_fd, "Failure to fork");
	}
	else if (pid == 0){
		exec_child(argv, env_cast, pipe_fd);
		exit_exec_cgi(env, env_cast, pipe_fd, "Dup2 fail");
		exit(0);
	}

	int status = 0;
	waitpid(pid, &status, 0);

	cout << YELLOW << status << RESET << endl;

	// string test = readFromFD(pipe_fd[0]);

	
	// cout << YELLOW << test << RESET << endl;

	// execve("/bin/test", ["/bin/test", "-s", "ereerer"], env);

	// char** ptr = env_cast;

    // while (*ptr) {
    //     cout << string(*ptr) << endl;
    //     ptr++;
    // }

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	freeCopy(env, env_cast);


	return "OK";
}