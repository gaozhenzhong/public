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
    class tcpSvrAndLoop
    {
    public:
        tcpSvrAndLoop(InetAddress & _listenAddr,connServer *_cServer);
        void loop(void){loop_.loop();}
        void quit(void){loop_.quit();}
    private:
        const int numThreads = 0;
        //TcpServer使用EventLoop所以定义顺序不能颠倒，否在析构和构造会存在问题
        EventLoop            loop_;
        TcpServer            server_;
    } ;

private:
    std::function<void(void)>  tcpSvrQuit;

    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);
    void csvrThread(void);

    std::string          ip_;
    int                  port_;
    InetAddress          listenAddr_;
    MutexLock            mutex_;
    Thread               thread_;
};

#endif // CONNSERVER_H
