#ifndef BUFTOORDER_H
#define BUFTOORDER_H
#include <memory>

#include<vector>
#include<deque>

#include "muduo/net/Buffer.h"
enum  orderID
{
    REPLAY,
    REGIST,
    ORDERID_END,
}  ;

struct registOrder
{
    int devType;
} ;


struct devOneOrder
{

    devOneOrder():len(0),orderID(ORDERID_END){memset(data,0,sizeof(data));}
    int           len ;
    enum  orderID orderID;
    char  data[1024];
};

class BufToOrder
{
public:
    BufToOrder(){}
    BufToOrder(const char*,int len);
    void AddNewData(const char*,int len);
    int  GetOneOrder(char*order);
private:
    void FindOrderInBuf();
    muduo::net::Buffer dataBuf_;
    std::deque<std::unique_ptr<struct devOneOrder>>  orderBuf_;
};

#endif // BUFTOORDER_H
