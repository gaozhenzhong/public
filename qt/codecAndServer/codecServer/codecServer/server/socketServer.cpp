#include "socketServer.h"
#include <functional>

socketServer::socketServer(std::string _ip,int _port)
    : thread( std::unique_ptr<muduo::Thread> (new muduo::Thread(std::bind(&socketServer::acceptThread,this))) ),
      ip(_ip),
      port(_port)
{

}
bool socketServer::threadStart(void)
{
    bool rst = false;
    thread->start();
    rst = true;
    return rst;
}
void socketServer::acceptThread(void)
{
    std::cout<<"socketServer::acceptThread start"<<std::endl;
}
