#ifdef WIN32
#include "WinsockClient.h"
#elif !WIN32
#include "UnixClient.h"
#endif // !WIN32

int __cdecl main(int argc, char** argv)
{
#ifdef WIN32
    WinsockClient server;
    server.Update();
#elif !WIN32
    UnixClient server;
#endif // !WIN32

    return 0;
}