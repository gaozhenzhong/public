#include "codecDev.h"
#include "ui_codecDev.h"
#include "base/baseFunction.h"

#include <qvalidator.h>
#include <QHostAddress>
#include <QAbstractSocket>
enum  orderID
{
    REPLAY,
    REGIST,
}  ;



struct registOrder
{
    int devType;
} ;

codecDev::orderData::orderData(char id,char* _data,char _size)
    :len_( 0 )
{
#if 0
    order_.insert(order_.end(),_size+10);
    order_.insert(order_.end(),id);
    for(int n = 0 ;n<_size;n++) order_.insert(order_.end(),_data[n]);
    order_.insert(order_.end(),'5');
    order_.insert(order_.end(),'5');
    order_.insert(order_.end(),'F');
    order_.insert(order_.end(),'F');
    order_.insert(order_.end(),'5');
    order_.insert(order_.end(),'5');
    order_.insert(order_.end(),'F');
    order_.insert(order_.end(),'F');
#else
    memcpy(order_,orderHeadStr,orderHeadLen);
    order_[orderLenAddr] = static_cast<char>(_size+1);//id+data 的长度
    order_[orderIDAddr]  = static_cast<char>(id);
    memcpy(order_+orderIDDataAddr,_data,_size);
    memcpy(order_+orderIDAddr+_size+1,orderTailStr,orderTailLen);
    len_ = orderIDAddr+1+_size+orderTailLen;
#endif
}

codecDev::codecDev(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::codecDev)
    ,tcpSocket(NULL)
{
    ui->setupUi(this);
    //设置界面的显示数据范围
    class QValidator *validator=new QIntValidator(0,99999,this);
    ui->portLineEdit->setValidator(validator);
}

codecDev::~codecDev()
{
    delete ui;
}

void codecDev::on_conPushButton_clicked()
{
    bool ok;
    if(tcpSocket == NULL)
    {
        QString ip = ui->IPLineEdit->text();
        int port   = ui->portLineEdit->text().toInt(&ok);
        QByteArray ba = ip.toLatin1();
        bool isAddr =kBaseFunction::isCurrectIP(ba.data());
        if(!isAddr)
        {
           ui->logTextBrowser->append(ip+" is no ip!");
        }
        //分配空间，指定父对象
        tcpSocket = new QTcpSocket(this);

        tcpSocket->connectToHost(QHostAddress(ip), port);

        ui->conPushButton->setText("disconnet");

        connect(tcpSocket, &QTcpSocket::connected,
            [=]()
            {
                struct registOrder data;
                data.devType   = 1;
                codecDev::orderData order(static_cast<char>(REGIST) ,reinterpret_cast<char*>(&data),static_cast<char>(sizeof(data)));
                tcpSocket->write(order.order_,order.len_);
                ui->logTextBrowser->append(QString("%1 : %2 : connect success").arg(ip).arg(port));
            }
        );

        //因为tcpSocket已经分配了空间，有指向，所以可以放在外面
        connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
            {
                //获取对方发送的内容
                QByteArray array = tcpSocket->readAll();
                //追加到编辑区中
                ui->logTextBrowser->append(QString("%1 : %2 : rec: %3").arg(ip).arg(port).arg(array.data()));
                //todo:添加数据函数
                process_netCmd(array);
            }
        );

        connect(tcpSocket, &QTcpSocket::disconnected,
            [=]()
            {
                ui->logTextBrowser->append(QString("%1 : %2 :disconnected").arg(ip).arg(port));
            }
        );
    }
    else
    {
        delete tcpSocket;
        tcpSocket = NULL;
        ui->conPushButton->setText("connet");
    }
//void stateChanged(QAbstractSocket::SocketState);
//void error(QAbstractSocket::SocketError);
}

void codecDev::on_sendOrderButton_clicked()
{
    QString sendOrder = ui->sendOrderLineEdit->text();
    tcpSocket->write(sendOrder.toUtf8().data());
}

bool codecDev::process_netCmd(QByteArray & _bArray)
{
    bool rst = false;
    ui->recOrderBrowser->append(QString("rec order form server: %1").arg(_bArray.data()));
    return rst=true;
}
