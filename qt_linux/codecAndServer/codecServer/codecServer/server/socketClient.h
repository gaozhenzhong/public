#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include<iostream>
#include <strings.h>

class socketClient
{
public:
    socketClient();
private:
    int sktFd;
    std::string  sktIP;
    int sktPort;

};

#endif // SOCKETCLIENT_H
