#include "connServer.h"

connServer::connServer(std::string _ip,int _port)
    : ip_(_ip),
      port_(_port),
      listenAddr_(_port, false, false),
      server_(&loop_, listenAddr_, "connServer"),
      thread_(std::bind(&EventLoop::loop,&loop_))
{
    LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
    LOG_INFO << "sizeof TcpConnection = " << sizeof(TcpConnection);
    server_.setConnectionCallback(
        std::bind(&connServer::onConnection, this, _1));
    server_.setMessageCallback(
        std::bind(&connServer::onMessage, this, _1, _2, _3));
    server_.setThreadNum(numThreads);
    server_.start();
    thread_.start();
}

connServer::~connServer(void)
{
    loop_.quit();
}
void connServer::onConnection(const TcpConnectionPtr& conn)
{
    LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
    LOG_INFO << conn->getTcpInfoString();

    conn->send("hello\n");
}

void connServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
    string msg(buf->retrieveAllAsString());
    LOG_TRACE << conn->name() << " recv " << msg.size() << " bytes at " << time.toString();
    if (msg == "exit\n")
    {
      conn->send("bye\n");
      conn->shutdown();
    }
    conn->send(msg);
}
