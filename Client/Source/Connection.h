#pragma once

#include <WinSock2.h>

struct Connection
{
	SOCKET mySocket;
	addrinfo myHints;
	addrinfo* myResult;
	addrinfo* myPointer;
	const char* myServerName;
};