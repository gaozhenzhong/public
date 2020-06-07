#include "connServer.h"
connServer::tcpSvrAndLoop::tcpSvrAndLoop(InetAddress & _listenAddr,connServer* _cServer)
    :server_(&loop_, _listenAddr, "connServer")
{
    server_.setConnectionCallback(
        std::bind(&connServer::onConnection, _cServer, _1));
    server_.setMessageCallback(
        std::bind(&connServer::onMessage, _cServer, _1, _2, _3));
    server_.setThreadNum(numThreads);
    server_.start();
}

connServer::connServer(std::string _ip,int _port)
    : ip_(_ip),
      port_(_port),
      listenAddr_(_port, false, false),
      thread_(std::bind(&connServer::csvrThread,this))
{
    LOG_INFO << "start :pid = " << getpid() << ", tid = " << CurrentThread::tid();
    thread_.start();
}

connServer::~connServer(void)
{
    tcpSvrQuit();
    thread_.join();
    LOG_INFO << "end :pid = " << getpid() << ", tid = " << CurrentThread::tid();
}

void connServer::csvrThread(void)
{
    LOG_INFO << "start :pid = " << getpid() << ", tid = " << CurrentThread::tid();
    std::unique_ptr<connServer::tcpSvrAndLoop> tcpSvrPtr(new connServer::tcpSvrAndLoop(listenAddr_,this));
    //tcpServer_=std::unique_ptr<connServer::tcpServer> (new connServer::tcpServer(listenAddr_,this));
    tcpSvrQuit = std::bind(&connServer::tcpSvrAndLoop::quit,tcpSvrPtr.get());

    tcpSvrPtr->loop();

    LOG_INFO << "end :pid = " << getpid() << ", tid = " << CurrentThread::tid();
}

void connServer::onConnection(const TcpConnectionPtr& conn)
{
    LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
    LOG_INFO << conn->getTcpInfoString();
    //conn->send("hello\n");

}

void connServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
    string msg(buf->retrieveAllAsString());
    LOG_TRACE << conn->name() << " recv " << msg.size() << " bytes at " << time.toString();
#if 1
    if (msg == "exit\n")
    {
      conn->send("bye\n");
      conn->shutdown();
    }
    conn->send(msg);
#else

#endif
}
