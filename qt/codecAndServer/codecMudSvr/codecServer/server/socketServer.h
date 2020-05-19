#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#include "muduo/base/Thread.h"
#include "muduo/base/noncopyable.h"
#include "codecDev.h"
#include <memory.h>
#include <iostream>

class socketServer : muduo::noncopyable
{
public:
    explicit socketServer(std::string _ip,int _port);
    bool     threadStart(void);
    bool     threadEnd(void);
    void     acceptThread(void);
    typedef  std::function<void (codecDev &cDev)> creatNewCdev;
private:
    void setnonblocking(int sockfd);
private:
    muduo::MutexLock     mutex_;
    bool threadIsRunning;
    std::unique_ptr<muduo::Thread> thread;
    std::string ip;
    int port;
    int serverLstFd;
};

#endif // SOCKETSERVER_H
