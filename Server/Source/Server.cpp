#ifdef WIN32
#include "WinsockServer.h"
#elif !WIN32
#include "UnixServer.h"
#endif // WIN32

int __cdecl main(void)
{
#ifdef WIN32
    WinsockServer server;
#elif !WIN32
#include "UnixServer.h"
    UnixServer server;
#endif // WIN32

    return 0;
}