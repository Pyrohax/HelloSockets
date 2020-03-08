#ifdef WIN32
#include "WinsockClient.h"
#include "Connection.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_PORT "27015"

WinsockClient::WinsockClient() : myConnection(nullptr), myShouldClose(false)
{
}

WinsockClient::~WinsockClient()
{
}

bool WinsockClient::Connect(const char* aServerName)
{
    myConnection = new Connection();
    myConnection->myServerName = aServerName;

    Startup();

    myConnection->mySocket = INVALID_SOCKET;
    myConnection->myResult = nullptr;
    myConnection->myPointer = nullptr;

    ZeroMemory(&myConnection->myHints, sizeof(myConnection->myHints));
    myConnection->myHints.ai_family = AF_UNSPEC;
    myConnection->myHints.ai_socktype = SOCK_STREAM;
    myConnection->myHints.ai_protocol = IPPROTO_TCP;

    if (!ResolveConnection())
        return false;

    if (!TryConnectToAddress())
        return false;

    freeaddrinfo(myConnection->myResult);

    if (!ValidateConnection())
        return false;
}

bool WinsockClient::Update()
{
    while (!myShouldClose)
    {
        std::string input;
        std::cout << "Enter a message:" << std::endl;
        std::cin >> input;

        if (input.length() > 0)
        {
            Send(input.c_str());
            myShouldClose = true;
        }

        char buffer[512];
        Receive(buffer, 512);

        if (buffer > 0)
        {
            std::cout << buffer << std::endl;
        }
        else if (buffer == 0)
        {
            printf("Connection closed\n");
        }
        else
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
        }

        myShouldClose = true;
    }

    return true;
}

bool WinsockClient::Startup()
{
    WSADATA wsaData;
    const int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        printf("WSAStartup failed with error: %d\n", result);
        return false;
    }

    return true;
}

bool WinsockClient::ResolveConnection()
{
    const int result = getaddrinfo(myConnection->myServerName, DEFAULT_PORT, &myConnection->myHints, &myConnection->myResult);
    if (result != 0)
    {
        printf("getaddrinfo failed with error: %d\n", result);
        WSACleanup();
        return false;
    }

    return true;
}

bool WinsockClient::TryConnectToAddress()
{
    for (myConnection->myPointer = myConnection->myResult; myConnection->myPointer != nullptr; myConnection->myPointer = myConnection->myPointer->ai_next)
    {
        myConnection->mySocket = socket(myConnection->myPointer->ai_family, myConnection->myPointer->ai_socktype, myConnection->myPointer->ai_protocol);
        if (myConnection->mySocket == INVALID_SOCKET)
        {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return false;
        }

        const int result = connect(myConnection->mySocket, myConnection->myPointer->ai_addr, (int)myConnection->myPointer->ai_addrlen);
        if (result == SOCKET_ERROR)
        {
            closesocket(myConnection->mySocket);
            myConnection->mySocket = INVALID_SOCKET;
            continue;
        }

        break;
    }

    return true;
}

bool WinsockClient::Send(const char* aMessage)
{
    const int result = send(myConnection->mySocket, aMessage, (int)strlen(aMessage), 0);
    if (result == SOCKET_ERROR)
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(myConnection->mySocket);
        WSACleanup();
        return false;
    }

    printf("Bytes Sent: %ld\n", result);
    
    return true;
}

bool WinsockClient::Close()
{
    const int result = shutdown(myConnection->mySocket, SD_SEND);
    if (result == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(myConnection->mySocket);
        WSACleanup();
        return false;
    }

    return true;
}

size_t WinsockClient::Receive(char* buffer, size_t size)
{
    size_t total = 0, n = 0;
    while ((n = ::recv(myConnection->mySocket, buffer + total, size - total - 1, 0)) > 0)
        total += n;

    buffer[total] = 0;
    return total;
}

bool WinsockClient::ValidateConnection()
{
    if (myConnection->mySocket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return false;
    }

    return true;
}
#endif // WIN32