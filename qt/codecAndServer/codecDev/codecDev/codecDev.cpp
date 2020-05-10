#include "codecDev.h"
#include "ui_codecDev.h"
#include "base/baseFunction.h"

#include <qvalidator.h>
#include <QHostAddress>
#include <QAbstractSocket>
codecDev::codecDev(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::codecDev)
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
    QString ip = ui->IPLineEdit->text();
    int port   = ui->portLineEdit->text().toInt(&ok);
    QByteArray ba = ip.toLatin1();
    bool isAddr =kBaseFunction::isCurrectIP(ba.data());
    if(!isAddr)
    {
       ui->logTextBrowser->append(ip+" is no ip!");
    }
    //分配空间，指定父对象
    tcpSocket = std::unique_ptr<QTcpSocket>(new QTcpSocket(this));
    tcpSocket->connectToHost(QHostAddress(ip), port);


    connect(tcpSocket.get(), &QTcpSocket::connected,
        [=]()
        {
            ui->logTextBrowser->append(QString("%1 : %2 : connect success").arg(ip).arg(port));
        }
    );

    //因为tcpSocket已经分配了空间，有指向，所以可以放在外面
    connect(tcpSocket.get(), &QTcpSocket::readyRead,
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

    connect(tcpSocket.get(), &QTcpSocket::disconnected,
        [=]()
        {
            ui->logTextBrowser->append(QString("%1 : %2 :disconnected").arg(ip).arg(port));
        }
    );
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
