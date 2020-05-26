#ifndef CONNSERVER_H
#define CONNSERVER_H
#include "muduo/net/TcpServer.h"

#include "muduo/base/Logging.h"
#include "muduo/base/Thread.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"

using namespace muduo;
using namespace muduo::net;

class connServer
{
public:
    ~connServer(void);
    connServer(std::string _ip = nullptr,int _port = 2000);

private:
    const int numThreads = 0;
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);

    std::string          ip_;
    int                  port_;
    EventLoop            loop_;
    InetAddress          listenAddr_;
    TcpServer            server_;
    MutexLock            mutex_;
    Thread               thread_;


};

#endif // CONNSERVER_H
