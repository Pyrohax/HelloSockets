#pragma once

#include <WinSock2.h>

struct Connection
{
	SOCKET mySocket;
	addrinfo myHints;
	addrinfo* myResult;
	addrinfo* myPointer;
	char myInMessage[512];
	const char* myOutMessage;
	const char* myServerName;
	int myInMessageBufferLength;
};