#ifdef WIN32
#include "WinsockClient.h"
#elif !WIN32
#include "UnixClient.h"
#endif // !WIN32

#include <iostream>

int __cdecl main(int argc, char** argv)
{
#ifdef WIN32
    WinsockClient client;

    std::string input;

    std::cout << "Enter the server name:" << std::endl;
    std::cin >> input;

    client.Connect(input.c_str());
    client.Send("Hello World!");
    client.Fetch();
    client.Close();
#elif !WIN32
    UnixClient client;
#endif // !WIN32

    return 0;
}