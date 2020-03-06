#ifndef WIN32
#include "UnixServer.h"
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

UnixServer::UnixServer()
{
}

UnixServer::~UnixServer()
{
}
#endif // !WIN32