#ifndef NETTOOL_H
#define NETTOOL_H

#include <QMainWindow>
#include<QStandardItemModel>
#include<QTcpSocket>
#include<QUdpSocket>
#include<QTcpServer>
#include <iostream>
//#define ENABLE_TREE_VIEW

QT_BEGIN_NAMESPACE
namespace Ui { class netTool; }
QT_END_NAMESPACE



class netTool : public QMainWindow
{
Q_OBJECT

public:
    netTool(QWidget *parent = nullptr);
    ~netTool();
private slots:
    void on_conButton_clicked();
    void on_CDevtreeView_clicked();
private:
    Ui::netTool *ui;
   // QStandardItemModel* model;
    std::unique_ptr<QStandardItemModel>  model;
    QStandardItem *getItem(QStandardItemModel *model, QString s);
    QStandardItem *getItem(QStandardItem *item, QString s);
    void CDevtreeViewInit(void);
#ifdef ENABLE_TREE_VIEW
    void CDevtreeViewTest(void);
#endif
//net
private:
/*
std::vector<std::unique_ptr<int>> ptrsToInts;
ptrsToInts.emplace_back(new int);
*/
    std::list<std::unique_ptr<QTcpServer>> TcpServerList;
    std::list<std::unique_ptr<QTcpSocket>> TcpClinetList;
    std::list<std::unique_ptr<QUdpSocket>> UdpServerList;
    std::list<std::unique_ptr<QUdpSocket>> UdpClinetList;
    typedef enum creatConnType
    {
        TCP_SERVER,
        TCP_CLINET,
        UDP_SERVER,
        UDP_CLINET,
        creatConnType_Max,
    }ecreatConnType;
    bool creatCon(enum creatConnType  _ConnType ,QString &_ip,QString &_port);
};
#endif // NETTOOL_H
