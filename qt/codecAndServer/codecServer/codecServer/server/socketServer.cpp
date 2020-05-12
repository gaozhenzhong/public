#include "socketServer.h"
#include <functional>
#include <unistd.h>
#include"muduo/base/Logging.h"
#include"muduo/base/CurrentThread.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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
    LOG_INFO<<" t_tid: "<<muduo::CurrentThread::t_tidString<<" name: "<<muduo::CurrentThread::t_threadName;
    while(1)
    {
        sleep(1);
        LOG_INFO<<"socketServer::acceptThread start";
    }
}

