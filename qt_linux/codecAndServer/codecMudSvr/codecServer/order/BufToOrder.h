#ifndef BUFTOORDER_H
#define BUFTOORDER_H
#include <memory>

#include<vector>
#include<deque>

#include "muduo/net/Buffer.h"
#include "base/cycleQueue.h"

#include "muduo/base/Logging.h"
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
    BufToOrder():cycleQueue_(10){}
    ~BufToOrder(){}
    void AddNewData(const char*,int len);
    int  GetOneOrder(char*order);
private:
    muduo::net::Buffer dataBuf_;
    cycleQueue<std::shared_ptr<struct devOneOrder>> cycleQueue_;
    void FindOrderInBuf();
};

#endif // BUFTOORDER_H
