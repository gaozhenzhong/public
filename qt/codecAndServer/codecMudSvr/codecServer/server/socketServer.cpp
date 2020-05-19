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
#include <sys/epoll.h>
#include <fcntl.h>

socketServer::socketServer(std::string _ip,int _port)
    : threadIsRunning(false),
      thread( std::unique_ptr<muduo::Thread> (new muduo::Thread(std::bind(&socketServer::acceptThread,this))) ),
      ip(_ip),
      port(_port)
{

}
void socketServer::setnonblocking(int sockfd)
{
    int opts;

    opts = fcntl(sockfd, F_GETFL);
    if(opts < 0) {
        LOG_ERROR<<"fcntl(F_GETFL)\n";
        exit(1);
    }
    opts = (opts | O_NONBLOCK);
    if(fcntl(sockfd, F_SETFL, opts) < 0) {
        LOG_ERROR<<"fcntl(F_SETFL)\n";
        exit(1);
    }
}

bool socketServer::threadStart(void)
{
    bool rst = false;
    int  opt;
    struct sockaddr_in server;
    if(threadIsRunning)
    {
        LOG_INFO<<"server is running!";
        return rst;
    }
    if (-1==(serverLstFd=socket(AF_INET,SOCK_STREAM,0)))
    {
         LOG_ERROR<<"create listen socket error info： "<<serverLstFd<<strerror(errno);
         exit(1);
    }

    //setReuseaddr(serverLstFd);
    setnonblocking(serverLstFd);
    if (setsockopt(serverLstFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
         LOG_ERROR<<"socket setsockopt error. info： "<<serverLstFd<<strerror(errno);
         exit(1);
    }

    memset(&server,0,sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);//表示的是一个服务器上所有的网卡
    server.sin_port = htons(port);

    if (-1==bind(serverLstFd,(struct sockaddr *)&server,sizeof(struct sockaddr)))
    {
        LOG_ERROR<<"bind error info： "<<serverLstFd<<strerror(errno);
        exit(1);
    }
    if (-1==listen(serverLstFd,10))  //10:等待连接队列的最大长度。
    {
        LOG_ERROR<<"listen error info： "<<serverLstFd<<strerror(errno);
        exit(1);
    }
   // LOG_INFO<<"serverLstFd = "<<serverLstFd;
    threadIsRunning = true;
    thread->start();
    rst = true;
    return rst;
}

bool socketServer::threadEnd(void)
{
    bool rst = true;
    threadIsRunning = false;
    thread->join();
    LOG_INFO<<"server stop!";
    return rst;
}
/*
调用shutdown和close并不能够让accept（）自动返回，郁闷！要调用select()才能实现我要的功能，select除了socket的fd外，还要创建pipe，让select也可以选择pipe的fd.
要退出的时候，需先向pipe中写入内容来interrupt select()，select()返回后就可以检测accept socket是否要求关闭。如果要求关闭，只要shutdown和close socket并退出accept线程即可。
*/
void socketServer::acceptThread(void)
{
    int    clientConFd;
    struct sockaddr_in client;
    int    len =  sizeof(sockaddr_in);
    int    epfd;
    const int EpollMaxEvent = 10;
    struct epoll_event ev, events[EpollMaxEvent];
    int    nfds=-1;
    int    nread, n;
    const int netWRBufSize = 128;
    char   buf[netWRBufSize];

    LOG_INFO<<"acceptThread start； t_tid: "<<muduo::CurrentThread::t_tidString<<" name: "<<muduo::CurrentThread::t_threadName;

    epfd = epoll_create(EpollMaxEvent);
    if (epfd == -1) {
       LOG_ERROR<<"epoll_create";
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = serverLstFd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, serverLstFd, &ev) == -1) {
        LOG_ERROR<<"epoll_ctl: listen_sock";
        exit(EXIT_FAILURE);
    }

    while(threadIsRunning)
    {
        nfds = epoll_wait(epfd, events, EpollMaxEvent, 100);//100毫秒用于检测结束使用
        if (nfds == -1) {
            LOG_ERROR<<"epoll_pwait";
            exit(EXIT_FAILURE);
        }
        if(!threadIsRunning)
        {
            //todo:断开clinet端；
            if(close(serverLstFd)<0)
            {
                LOG_ERROR<<"LstFd close error. info： "<<serverLstFd<<strerror(errno);
            }
        }
        for (int i = 0; i < nfds; ++i) {
            int fd = events[i].data.fd;
            if (fd == serverLstFd) {
                while ((clientConFd = accept(serverLstFd,(struct sockaddr*)&client,(socklen_t *)&len)) > 0) {
                    setnonblocking(clientConFd); //设置连接socket为非阻塞
                    ev.events = EPOLLIN | EPOLLET; //边沿触发要求套接字为非阻塞模式；水平触发可以是阻塞或非阻塞模式
                    ev.data.fd = clientConFd;
                    if (epoll_ctl(epfd, EPOLL_CTL_ADD, clientConFd,&ev) == -1) {
                        LOG_ERROR<<"epoll_ctl: add";
                        exit(EXIT_FAILURE);
                    }
                }
               if (clientConFd == -1) {
                    if (errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)
                        LOG_ERROR<<"accept";
                }
                continue;
            }
            if (events[i].events & EPOLLIN) {
                n = 0;
                while ((nread = read(fd, buf + n, netWRBufSize-1)) > 0) {
                    n += nread;
                }
                if (nread == -1 && errno != EAGAIN) {
                    LOG_ERROR<<"read error";
                }
                ev.data.fd = fd;
                ev.events = events[i].events | EPOLLOUT;
                if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
                    LOG_ERROR<<"epoll_ctl: mod";
                }
            }
            /*
                使用Linux epoll模型，水平触发模式；当socket可写时，会不停的触发 socket 可写的事件，如何处理
                开始不把 socket 加入 epoll，需要向 socket 写数据的时候，直接调用 write 或者 send 发送数据。如果返回 EAGAIN，把 socket 加入 epoll，在 epoll 的驱动下写数据，全部数据发送完毕后，再移出 epoll。
             */
            if (events[i].events & EPOLLOUT) {
                sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);
                int nwrite, data_size = strlen(buf);
                n = data_size;
                while (n > 0) {
                    nwrite = write(fd, buf + data_size - n, n);
                    if (nwrite < n) {
                        if (nwrite == -1 && errno != EAGAIN) {
                            LOG_ERROR<<"write error";
                        }
                        break;
                    }
                    n -= nwrite;
                }
                close(fd);
            }
        }
    }
}


