#include "BufToOrder.h"
#include "muduo/base/Logging.h"
#include <string.h>
#include "base/cycleQueue.h"

const char *orderHeadStr     = "FF55FF55";
//const char orderHeadLen      = 8;
const int  orderLenAddr      = 8;
const int  orderIDAddr       = 9;
const char orderIDDataAddr   = 10;
const char *orderTailStr     = "55FF55FF";
const char orderTailLen      = 8;

void BufToOrder::FindOrderInBuf()
{
    const char* begin = dataBuf_.peek();
    size_t offset = 0;
    while(dataBuf_.readableBytes()>offset)
    {
        if((*begin == 'F')&&(*(begin+1)=='F')&&(*(begin+6)=='5')&&(*(begin+7)=='5'))
        {
            char orderLen = *(begin+orderLenAddr);
            if(static_cast<size_t>(orderIDDataAddr+orderLen+orderTailLen)<=dataBuf_.readableBytes())
            {
                if((*(begin+orderIDDataAddr+orderLen) == '5')&&(*(begin+orderIDDataAddr+orderLen+1)=='5')
                        &&(*(begin+orderIDDataAddr+orderLen+6)=='F')&&(*(begin+orderIDDataAddr+orderLen+7)=='F'))
                {
                    struct devOneOrder order ;
                    order.len = orderLen;
                    order.orderID = static_cast<enum  orderID>(*(begin+orderIDAddr)) ;
                    memcpy(order.data,begin+orderIDDataAddr,static_cast<int>(orderLen));
                    LOG_DEBUG<<"order info : len = "<<order.len<<"ID = "<<order.orderID;
                    cycleQueue_.push(order);
                }
            }
            else
            {
                break;
            }
            offset += orderIDDataAddr+orderLen+orderTailLen;
        }
        offset++;
        begin++;
    }
    LOG_DEBUG<<"offset = "<<offset;
}

void BufToOrder::AddNewData(const char* _data,int _len)
{
    dataBuf_.append(_data,_len);
    FindOrderInBuf();
    LOG_DEBUG<<_len;
}

int  BufToOrder::GetOneOrder( enum orderID & _orderID ,char*_order)
{
    int rst = 0;

    if(!cycleQueue_.isEmpty() )
    {
        struct devOneOrder order =  cycleQueue_.pop();
        memcpy(_order, order.data,order.len);
        _orderID = order.orderID;
        rst = 1;
    }

    return rst;
}

