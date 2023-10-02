#include "response.hpp"
#include <unistd.h>

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
	// DEBUG_INFO_ << "l_read = " << length_read << "[" << (int) buffer[0] << "] [" << (int) buffer[1] << "]" << endl;
	if (length_read < 0){
		r_status = S_ERROR;
		DEBUG_WARN_ << "Failed to read from socket: " << errno << endl;
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