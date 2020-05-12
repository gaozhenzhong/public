#include "socketServer.h"
#include <functional>
#include <unistd.h>
#include"muduo/base/Logging.h"

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
    while(1)
    {
        sleep(1);
        LOG_INFO<<"socketServer::acceptThread start";
    }
}

