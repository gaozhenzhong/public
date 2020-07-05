#ifndef ORDER_H
#define ORDER_H
#include "connServer.h"
#include"./order/BufToOrder.h"
class order
{
public:
    order();
public:
    void muduoOnMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);
private:
    BufToOrder BufToOrder_;
};

#endif // ORDER_H
