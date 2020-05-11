#include "socketServer.h"
#include <functional>

socketServer::socketServer(std::string _ip,int _port)
    :thread(std::unique_ptr<muduo::Thread> (new muduo::Thread(std::bind(&socketServer::acceptThread,this)))),
      ip(_ip),
      port(_port)
{

}
