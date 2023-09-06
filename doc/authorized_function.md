### `execve`

- **Description:** Executes a new program.
- **Usage:** `int execve(const char *filename, char *const argv[], char *const envp[]);`

### `dup`

- **Description:** Duplicates a file descriptor.
- **Usage:** `int dup(int oldfd);`

### `dup2`

- **Description:** Duplicates a file descriptor to a specific descriptor number.
- **Usage:** `int dup2(int oldfd, int newfd);`

### `pipe`

- **Description:** Creates a pipe, a unidirectional communication channel.
- **Usage:** `int pipe(int pipefd[2]);`

### `strerror`

- **Description:** Returns a string describing the error code.
- **Usage:** `char *strerror(int errnum);`

### `gai_strerror`

- **Description:** Returns a string describing a getaddrinfo error code.
- **Usage:** `const char *gai_strerror(int errcode);`

### `errno`

- **Description:** Integer variable set by system calls and library functions on error.
- **Usage:** `extern int errno;`

### `fork`

- **Description:** Creates a new process by duplicating the calling process.
- **Usage:** `pid_t fork(void);`

### `htons`, `htonl`, `ntohs`, `ntohl`

- **Description:** Functions for converting between host and network byte order.
- **Usage:** `uint16_t htons(uint16_t hostshort);`, `uint32_t htonl(uint32_t hostlong);`, `uint16_t ntohs(uint16_t netshort);`, `uint32_t ntohl(uint32_t netlong);`

### `select`

- **Description:** Monitors multiple file descriptors for readiness.
- **Usage:** `int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);`

### `poll`

- **Description:** Polls multiple file descriptors for events.
- **Usage:** `int poll(struct pollfd fds[], nfds_t nfds, int timeout);`

### `epoll` (`epoll_create`, `epoll_ctl`, `epoll_wait`)

- **Description:** Provides efficient event notification on Linux.
- **Usage:** `int epoll_create(int size);`, `int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);`, `int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);`

### `kqueue` (`kqueue`, `kevent`)

- **Description:** Provides event notification on BSD-based systems.
- **Usage:** `int kqueue(void);`, `int kevent(int kq, const struct kevent *changelist, int nchanges, struct kevent *eventlist, int nevents, const struct timespec *timeout);`

### `socket`

- **Description:** Creates a socket endpoint for communication.
- **Usage:** `int socket(int domain, int type, int protocol);`

### `accept`

- **Description:** Accepts an incoming connection on a socket.
- **Usage:** `int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`

### `listen`

- **Description:** Listens for incoming connections on a socket.
- **Usage:** `int listen(int sockfd, int backlog);`

### `send`, `recv`

- **Description:** Send and receive data on a socket.
- **Usage:** `ssize_t send(int sockfd, const void *buf, size_t len, int flags);`, `ssize_t recv(int sockfd, void *buf, size_t len, int flags);`

### `bind`

- **Description:** Binds a socket to a specific address and port.
- **Usage:** `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`

### `connect`

- **Description:** Initiates a connection on a socket.
- **Usage:** `int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`

### `getaddrinfo`, `freeaddrinfo`

- **Description:** Resolves hostnames and service names into socket addresses.
- **Usage:** `int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);`, `void freeaddrinfo(struct addrinfo *res);`

### `setsockopt`

- **Description:** Sets options on a socket.
- **Usage:** `int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);`

### `getsockname`

- **Description:** Retrieves the local address of a socket.
- **Usage:** `int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`

### `getprotobyname`

- **Description:** Retrieves protocol information by name.
- **Usage:** `struct protoent *getprotobyname(const char *name);`

### `fcntl`

- **Description:** Performs various file control operations.
- **Usage:** `int fcntl(int fd, int cmd, ...);`

### `close`

- **Description:** Closes a file descriptor.
- **Usage:** `int close(int fd);`

### `read`, `write`

- **Description:** Reads from or writes to a file descriptor.
- **Usage:** `ssize_t read(int fd, void *buf, size_t count);`, `ssize_t write(int fd, const void *buf, size_t count);`

### `waitpid`

- **Description:** Waits for a specific child process to terminate.
- **Usage:** `pid_t waitpid(pid_t pid, int *status, int options);`

### `kill`

- **Description:** Sends a signal to a process.
- **Usage:** `int kill(pid_t pid, int sig);`

### `signal`

- **Description:** Sets a function to handle a specific signal.
- **Usage:** `void (*signal(int sig, void (*handler)(int)))(int);`

### `access`

- **Description:** Checks whether a file or directory can be accessed.
- **Usage:** `int access(const char *pathname, int mode);`

### `stat`

- **Description:** Retrieves file status information.
- **Usage:** `int stat(const char *pathname, struct stat *statbuf);`

### `opendir`, `readdir`, `closedir`

- **Description:** Functions for working with directories.
- **Usage:** `DIR *opendir(const char *name);`, `struct dirent *readdir(DIR *dirp);`, `int closedir(DIR *dirp);`
