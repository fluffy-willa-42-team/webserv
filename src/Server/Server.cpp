#include "Server.hpp"
#include "Request.hpp"
#include <fcntl.h>
#include <stdlib.h>

/* ************************************************************************** */

#define TEST_MESSAGE "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!"
#define TEST_MESSAGE_LEN 74

/* ************************************************************************** */



/**
 * @brief Will start the server instance
 */
void Server::start(){
	is_running = true;
	server_fd = socket(address.input.sin_family, SOCK_STREAM, 0);
	if (server_fd < 0)
		throw InternalError("failed to created socket server");
	int status = bind(server_fd, &address.data, address.len);
	if (status < 0)
		throw InternalError("failed to bind socket server to port");
	status = listen(server_fd, 256);
	if (status < 0)
		throw InternalError("failed to listen to socket server");
	cout << RED << "Listening on " << address << RESET << endl;
	
	start_loop();
}



/**
 * @brief Starts the main loop. Its waiting for all connection takes the first
 * in the backlog and executes it.
 */
void Server::start_loop(){
	while(is_running)
	{
		cout << GREEN << "----- Waiting for new connection (" << address << ") -----" << RESET << endl << endl;

		connection_fd = accept(server_fd, &address.data, address.get_socklen());
		if (connection_fd < 0){
			if (is_running){
				cout << is_running << " " << connection_fd << endl;
				throw InternalError();
			}
			return ;
		}
		
		exec_connection();

		close(connection_fd);
	}
}



/**
 * @brief Execute a connection
 */
void Server::exec_connection(){
	read(connection_fd, buffer, BUFFER_SIZE);
	cout << buffer << endl;

	Request test(buffer);

	cout << BLUE << "----- Test Request -----" << RESET << endl << endl;

	cout << test << endl;

	reset_buffer();
	write(connection_fd , TEST_MESSAGE, TEST_MESSAGE_LEN);
}



/* ************************************************************************** */



/**
 * @brief Will start a server inside a fork of the process
 */
void Server::start_parallel(){
	pid_t pid = fork();
	if (pid == 0)
	{
		try{
			this->start();
		}
		catch(const std::exception& e){
			std::cerr << e.what() << '\n';
		}
		exit(0);
	}
}



/**
 * @brief Stops the server instance
 */
void Server::stop(){
	if (!is_running)
		return ;
	is_running = false;
	if (server_fd >= 0){
		close(server_fd);
		server_fd = -1;
	}
	if (connection_fd >= 0){
		close(connection_fd);
		connection_fd = -1;
	}
	cout << endl << RED << "Closed " << address << RESET << endl;
}


