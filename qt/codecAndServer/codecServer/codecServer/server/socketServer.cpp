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
    struct sockaddr_in server;

    if (-1==(serverLstFd=socket(AF_INET,SOCK_STREAM,0)))
    {
         LOG_ERROR<<"create listen socket error\n";
         exit(1);
    }

    memset(&server,0,sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);//表示的是一个服务器上所有的网卡
    server.sin_port = htons(port);

    if (-1==bind(serverLstFd,(struct sockaddr *)&server,sizeof(struct sockaddr)))
    {
        LOG_ERROR<<"bind error\n";
        exit(1);
    }

    if (-1==listen(serverLstFd,5))  //5:等待连接队列的最大长度。
    {
        LOG_ERROR<<"listen error\n";
        exit(1);
    }

    thread->start();
    rst = true;
    return rst;
}
void socketServer::acceptThread(void)
{
    int clientConFd;
    struct sockaddr_in client;
    int len;
    LOG_INFO<<" t_tid: "<<muduo::CurrentThread::t_tidString<<" name: "<<muduo::CurrentThread::t_threadName;
    LOG_INFO<<"socketServer::acceptThread start";

    while(1)
    {
        sleep(1);
        if (-1==(clientConFd = ::accept(serverLstFd,(struct sockaddr*)&client,(socklen_t *)&len)))
        {
            LOG_ERROR<<"create connect socket error\n";
            continue;
        }

 #if 0
        sendnum = sprintf(send_buf,"hello,the guest from %s\n",inet_ntoa(client.sin_addr));
        if ( 0 >send(connectd,send_buf,sendnum,0))
        {
            perror("send error\n");
            close(connectd);
            continue;
        }


        if (0>(recvnum = recv(connectd,recv_buf,sizeof(recv_buf),0)))
        {
            perror("recv error\n");
            close(connectd);
            continue;
        }
        recv_buf[recvnum]='\0';

        printf ("the message from the client is: %s\n",recv_buf);

        if (0==strcmp(recv_buf,"quit"))
            {
            perror("the client break the server process\n");
            close(connectd);
            break;
        }

        sendnum = sprintf(send_buf,"%s\n",recv_buf);
#endif
        send(clientConFd,"will close",sizeof("will close"),0);

        close(clientConFd);
    }
}

