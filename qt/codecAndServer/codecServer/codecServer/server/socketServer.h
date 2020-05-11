#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#include "muduo/base/Thread.h"
#include <memory.h>
#include <iostream>

class socketServer
{
public:
    explicit socketServer(std::string _ip,int _port);
    void acceptThread(void);

private:
    std::unique_ptr<muduo::Thread> thread;
    std::string ip;
    int  port;
};

#endif // SOCKETSERVER_H
