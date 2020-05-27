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
    class tcpServer
    {
    public:
        tcpServer(InetAddress & _listenAddr,connServer *_cServer);
        ~tcpServer(void){

         }
        void loop(void)
        {
            loop_.loop();
        }
        void quit(void){

            loop_.quit();
        }
    private:
        const int numThreads = 0;
        EventLoop            loop_;
        TcpServer            server_;
    } *tcpServer_ = NULL;
    ~connServer(void);
    connServer(std::string _ip = nullptr,int _port = 2000);
    void     csvrThread(void);

private:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);

    std::string          ip_;
    int                  port_;
    InetAddress          listenAddr_;
    MutexLock            mutex_;
    Thread               thread_;
};

#endif // CONNSERVER_H
