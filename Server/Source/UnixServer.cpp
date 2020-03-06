#ifndef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT "3490" // the port users will be connecting to
#define BACKLOG 10 // how many pending connections queue will hold

void sigchld_handler(int s)
{
	// waitpid() might overwrite errno, so we save and restore it:
	int saved_errno = errno;

	while (waitpid(-1, NULL, WNOHANG) > 0);

	errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void* get_in_addr(structsockaddr* sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((structsockaddr_in*)sa)->sin_addr);
	}

	return &(((structsockaddr_in6*)sa)->sin6_addr);
}

int main()
{
	return 0;
}
#endif // !WIN32