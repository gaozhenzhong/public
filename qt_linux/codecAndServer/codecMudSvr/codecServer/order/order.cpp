#include "order.h"
#include <QApplication>

order::order()
{

}

void order::muduoOnMessage(const TcpConnectionPtr& _conn, Buffer* _buf, Timestamp _time)
{
    Q_UNUSED(_conn);
    Q_UNUSED(_time);

    char orderData[1024];
    enum orderID  ID ;
    LOG_DEBUG<<"get one data";
    size_t dataLen = _buf->readableBytes();
    BufToOrder_.AddNewData(_buf->peek(),dataLen);//peek 返回数据可读处
    _buf->retrieve(dataLen);

    while(BufToOrder_.GetOneOrder(ID,orderData))
    {
        LOG_DEBUG<<ID<<orderData;
    }
}
