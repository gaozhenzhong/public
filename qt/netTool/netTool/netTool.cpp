#include "netTool.h"
#include "ui_netTool.h"
#include "muduo/base/AsyncLogging.h"
#include "muduo/base/Logging.h"
#include<QDebug>
#include<iostream>
#include<QStandardItemModel>
#include<QHostAddress>
#include"baseClass.h"
//todo::不同实现方式的性能对比：qt，自己、mudo等
typedef enum creatConnType
{
    TCP_SERVER,
    TCP_CLINET,
    UDP_SERVER,
    UDP_CLINET,
    creatConnType_Max,
}ecreatConnType;

const int ConnTypeTreeAddr     = 102;
const int ConnTypeDataTreeAddr = 101;

netTool::netTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::netTool)
{
    ui->setupUi(this);
    setWindowTitle("网络调试工具");
    //表示绑定函数 fun 而fun 的第一，二个参数分别由调用 f2 的第一，二个参数指定
    netConFunc[0] = std::bind(&netTool::creatTCPSerCon,this,std::placeholders::_1,std::placeholders::_2);
    netConFunc[1] = std::bind(&netTool::creatTCPCltCon,this,std::placeholders::_1,std::placeholders::_2);
    netConFunc[2] = std::bind(&netTool::creatUDPSerCon,this,std::placeholders::_1,std::placeholders::_2);
    netConFunc[3] = std::bind(&netTool::creatUDPCltCon,this,std::placeholders::_1,std::placeholders::_2);

#ifdef ENABLE_TREE_VIEW
    CDevtreeViewTest();
#else
    CDevtreeViewInit();
#endif
}
netTool::~netTool()
{
    delete ui;
}
bool netTool::creatTCPSerCon(QString &_ip,QString &_port)
{
    bool res = false;
    bool ok;
    int port = _port.toInt(&ok);
    if(!ok)
    {
        qDebug()<<"port is no num\n";
    }
    QTcpServer *tcpServer = new QTcpServer(this);
    res = tcpServer->listen(QHostAddress::Any, port);
    if(!res) return res;

    QStandardItem *StandardItemSer = new QStandardItem(_ip+":"+_port);
    QVariant ItemVariant = QVariant::fromValue((void*)tcpServer);
    StandardItemSer->setData(ItemVariant,ConnTypeDataTreeAddr);//  树中存储数据
    StandardItemSer->setData(TCP_SERVER,ConnTypeTreeAddr);//  树中存储数据
    model->item(TCP_SERVER)->appendRow(StandardItemSer);

    connect(tcpServer, &QTcpServer::newConnection,
       [=]()//信号无参数，这里也没有参数
       {
            //取出建立好连接的套接字
            QTcpSocket  *tcpSocket = tcpServer->nextPendingConnection();
            //获取对方的IP和端口
            QString ip = tcpSocket->peerAddress().toString().split("::ffff:")[1];
            quint16 port= tcpSocket->peerPort();
            QString temp = QString("%1:%2").arg(ip).arg(port);
            QStandardItem *StandardItem = new QStandardItem(temp);
            QVariant ItemVariant = QVariant::fromValue((void*)tcpSocket);
            StandardItem->setData(ItemVariant,ConnTypeDataTreeAddr);
            StandardItem->setData(TCP_CLINET,ConnTypeTreeAddr);
            model->item(TCP_CLINET)->appendRow(StandardItem);
            ui->recBrowser->append(temp+":connet success");
            TCPSerSocketItem.push_back(StandardItem);
            //必须放在里面，因为建立好链接才能读，或者说tcpSocket有指向才能操作
            connect(tcpSocket, &QTcpSocket::readyRead,
                [=]()
                {
                    //从通信套接字中取出内容
                    QByteArray array = tcpSocket->readAll();
                    ui->recBrowser->append(temp+":"+array);
                }
            );        
       }
    );
   // 原文链接：https://blog.csdn.net/tt1995cc/java/article/details/70770042
    return res;
}
bool netTool::creatTCPCltCon(QString &_ip,QString &_port)
{
    bool res = false;
    bool ok;
    int port = _port.toInt(&ok);
    if(!ok)
    {
        qDebug()<<"port is no num\n";
    }
    qDebug()<<__FUNCTION__<<__LINE__<<"function achieve";
    //分配空间，指定父对象
    QTcpSocket* tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(QHostAddress(_ip), port);

    connect(tcpSocket, &QTcpSocket::connected,
        [=]()
        {
            QString temp = QString("%1:%2").arg(_ip).arg(_port);
            QStandardItem *StandardItem = new QStandardItem(temp);
            QVariant ItemVariant = QVariant::fromValue((void*)tcpSocket);
            StandardItem->setData(ItemVariant,ConnTypeDataTreeAddr);
            StandardItem->setData(TCP_CLINET,ConnTypeTreeAddr);
            model->item(TCP_CLINET)->appendRow(StandardItem);
            ui->recBrowser->append(temp+":connet success");
        }
    );
 //因为tcpSocket已经分配了空间，有指向，所以可以放在外面
    connect(tcpSocket, &QTcpSocket::readyRead,
        [=]()
        {
            //获取对方发送的内容
            QByteArray array = tcpSocket->readAll();
            //追加到编辑区中
            ui->recBrowser->append(_ip+":"+_port+":"+array);
        }
    );
    return res;
}
bool netTool::creatUDPSerCon(QString &_ip,QString &_port)
{
    bool res = false;
    qDebug()<<__FUNCTION__<<__LINE__<<"function achieve";
    return res;
}
bool netTool::creatUDPCltCon(QString &_ip,QString &_port)
{
    bool res = false;
    qDebug()<<__FUNCTION__<<__LINE__<<"function achieve";
    return res;
}
void netTool::on_conButton_clicked()
{
    bool res;
    QString ip   = ui->IPEdit->text();
    QByteArray ba = ip.toLatin1(); //
    bool _isAddr =nBaseClass::isCurrectIP(ba.data());
    if(_isAddr != true)
    {
        ui->recBrowser->append(ip+"is no ip");
        return;
    }
    QString port = ui->PortEdit->text();
    enum creatConnType connType = creatConnType(ui->connTypeComboBox->currentIndex());
    qDebug()<<connType<<ip<<port;
    if(connType>= creatConnType_Max)
    {
        ui->recBrowser->append("ConnType error");
        return;
    }
    res = netConFunc[connType]( ip,port);
    if(res)
    {
        ui->recBrowser->append(ip+port+":connet success");
    }
    else    //0为false
    {
        ui->recBrowser->append(ip+":"+port+":connet fail");
    }
#if 0
    ui->recBrowser->append(ip);
    ui->recBrowser->moveCursor(QTextCursor::End);
#endif
}

void netTool::CDevtreeViewInit()
{
    //treeview初始化
 #if 1
    std::unique_ptr<QStandardItemModel>  initModel(new QStandardItemModel(ui->CDevtreeView));
    model = std::move(initModel);//创建模型
#else
    model = std::move(std::unique_ptr<QStandardItemModel> (new QStandardItemModel(ui->CDevtreeView)));//创建模型
#endif
//TableView->setUpdatesEnabled(false);  //暂停界面刷新
    ui->CDevtreeView->setModel(model.get());//导入模型
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("地址")<<QStringLiteral("状态"));
    model->setItem(TCP_SERVER,0,new QStandardItem(tr("TCP服务端")));//0,0坐标值
    model->item(TCP_SERVER)->setData(creatConnType_Max,ConnTypeTreeAddr);
    model->setItem(TCP_SERVER,1,new QStandardItem(tr("0")));//0,0坐标值
    model->setItem(TCP_CLINET,0,new QStandardItem(tr("TCP客户端")));//0,0坐标值
    model->item(TCP_CLINET)->setData(creatConnType_Max,ConnTypeTreeAddr);
    model->setItem(TCP_CLINET,1,new QStandardItem(tr("0")));//0,0坐标值
    model->setItem(UDP_SERVER,0,new QStandardItem(tr("UDP服务端")));//  树中存储数据"UDP服务端")));
    model->item(UDP_SERVER)->setData(creatConnType_Max,ConnTypeTreeAddr);
    model->setItem(UDP_SERVER,1,new QStandardItem(tr("0")));
    model->setItem(UDP_CLINET,0,new QStandardItem(tr("UDP客户端")));
    model->item(UDP_CLINET)->setData(creatConnType_Max,ConnTypeTreeAddr);
    model->setItem(UDP_CLINET,1,new QStandardItem(tr("0")));
//TableView->setUpdatesEnabled(true);  //恢复界面刷新
}

QStandardItem *netTool::getItem(QStandardItemModel *model, QString s)
{
    QStandardItem *getitem = NULL;
    if(!model->hasChildren())//判断是否有孩子,没有则返回0
        return NULL;
    QList<QStandardItem*> list = model->findItems(s);
    qDebug() << tr("list is %1").arg(list.length());
    if(list.length() == 0)//如果链表长度为0，即没找到文本为s的条目
    {
        //将搜索子条目是否存在文本为s的条目
        for(int i = 0;i < model->rowCount()&& getitem == NULL;i++)//遍历model下的所有条目,如果getitem有获得对象，则退出循环
        {
            getitem = getItem(model->item(i),s);//寻找第i行条目下的子条目列中是否存在文本为s的条目。
        }
    }
    else
    {
        return list.at(0);
    }
    return getitem;
}

QStandardItem *netTool::getItem(QStandardItem *item, QString s)
{
    if(item == NULL)
        return NULL;
    qDebug() << tr("fine %1").arg(item->text());
    QStandardItem *getitem = NULL;
    if(item->text().compare(s) == 0)
        return item;
    if(!item->hasChildren())//判断是否有孩子,没有则返回0
        return NULL;
    for(int i = 0;i < item->rowCount() && getitem == NULL;i++)//遍历item下所有子条目，若果getitme有获得对象，则退出循环
    {
        QStandardItem * childitem = item->child(i);
        getitem = getItem(childitem,s);//寻找这个子条目的所有子条目是否存在文本为s的条目。
    }
    return getitem;
}
#if 0  //test code
        model->item(0)->appendRow(new QStandardItem(tr("10.100.8.18:99")));
        model->item(0)->appendRow(new QStandardItem(tr("10.100.8.18:98")));
    QString  testStr = "testdata";
    model->item(0)->setData(testStr,0);//  树中存储数据
    QVariant qVariant;
    qVariant=model->item(0)->data (0) ;
    //qDebug()<< qVariant.;
    QString  readStr = qVariant.toString() ;
    qDebug()<<readStr;
    {
        std::unique_ptr<QStandardItem> testItem( new QStandardItem(tr("10.100.8.18:99")) );
        nBaseClass::BaseTestClass test("test1");
        QTcpServer *tcpServer = new QTcpServer;
        QVariant var=QVariant::fromValue((void*)tcpServer);
        testItem->setData(var,0);
        //testItem->setData();
    }
#endif
#ifdef ENABLE_TREE_VIEW
void netTool::CDevtreeViewTest()
{
//https://blog.csdn.net/fangjiaze444/article/details/81569881
    //treeview初始化
    std::unique_ptr<QStandardItemModel>  initModel(new QStandardItemModel(ui->CDevtreeView));
    model = std::move(initModel);//创建模型
    ui->CDevtreeView->setModel(model.get());//导入模型
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("设备名")<<QStringLiteral("信息1")<<QStringLiteral("信息2"));
    //创建题目
    model->setItem(0,0,new QStandardItem(tr("item two")));//0,0坐标值
        model->item(0)->appendRow(new QStandardItem(tr("item four")));
//        model->item(0,1)->appendRow(new QStandardItem(tr("item 1222")));
    model->setItem(1,0,new QStandardItem(tr("item three")));
    //通过名字添加子项
    QList<QStandardItem*> list = model->findItems(tr("item two"));
    for(int i = 0;i<list.length();i++)
    {
        qDebug() << tr("list has ").append(list.at(i)->text());//打印该条目的文本
        //item变量指向这个Item two这个对象
        QStandardItem* item = list.at(i);
        /*参数1：item-row()是获取在上一级model或条目下自己所在的行号
        参数2: 1  是第1列，从第0列开始计数，故是相关信息1下的条目列
        参数3： 是创建一个对象,文本信息是item two msg*/
        model->setItem(item->row(),1,new QStandardItem(tr("item two msg")));
    }
    QStandardItem * getitem = getItem(model.get(),tr("item four"));
    getitem->parent()->setChild(getitem->row(),1,new QStandardItem(tr("item four msg")));
}
#endif
/*
 *treeView单击相应函数
 */
void netTool::on_CDevtreeView_clicked()
{
    QString selectTreeBranch;

    QModelIndex currentIndex = ui->CDevtreeView->currentIndex();
    currentItem = model->itemFromIndex(currentIndex);
    selectTreeBranch += currentItem->text();
    ui->CDevIfolabel->setText(selectTreeBranch);
    treeActiveConnType = currentItem->data(ConnTypeTreeAddr).toInt();
    qDebug()<<treeActiveConnType;
    activeSocket = currentItem->data(ConnTypeDataTreeAddr).value<void*>();
    qDebug()<<activeSocket;
}
void netTool::on_SendButton_clicked()
{
    QString sendStr = ui->SendEdit->document()->toPlainText() ;
    switch(treeActiveConnType)
    {
        case TCP_CLINET:
            QTcpSocket*  TSocket = (QTcpSocket*)activeSocket;
            TSocket->write(sendStr.toUtf8().data());
        break;
        #if 0
        case UDP_CLINET:
            QUdpSocket*  USocket = (QUdpSocket*)activeSocket;
            USocket->write(sendStr.toUtf8().data());
        break;
        #endif
    }
}
void netTool::on_DisconButton_clicked()
{
    if((activeSocket == NULL)||(currentItem == NULL))
    {
        qDebug()<<"activeSocket == NULL";
        return ;
    }
    switch(treeActiveConnType)
    {
        case TCP_SERVER:{
            for(auto iter = TCPSerSocketItem.begin();iter != TCPSerSocketItem.end();)
            {
                QStandardItem*   nowItem = *iter;
                QTcpSocket*  TSocket = (QTcpSocket*)nowItem->data(ConnTypeDataTreeAddr).value<void*>();
                //主动和客户端断开连接
                //TSocket->disconnectFromHost();
                TSocket->close();
                delete TSocket;
                TCPSerSocketItem.erase(iter++);
                nowItem->parent()->removeRow(nowItem->row());

            }
            QTcpServer*  TServer = (QTcpServer*)activeSocket;
            //主动和客户端断开连接
            TServer->close();
            delete TServer;
            activeSocket = NULL;
            currentItem->parent()->removeRow(currentItem->row());
        }
        break;
#if 1
        case TCP_CLINET:
         {
            QTcpSocket*  TSocket = (QTcpSocket*)activeSocket;
            //主动和客户端断开连接
            TSocket->disconnectFromHost();
            TSocket->close();
            delete TSocket;
            activeSocket = NULL;
            currentItem->parent()->removeRow(currentItem->row());
        }
        break;
#endif
    }
}
