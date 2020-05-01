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
    void on_SendButton_clicked();
    void on_DisconButton_clicked();
private:
    Ui::netTool *ui;
    std::unique_ptr<QStandardItemModel>  model;
    QStandardItem *getItem(QStandardItemModel *model, QString s);
    QStandardItem *getItem(QStandardItem *item, QString s);
    void CDevtreeViewInit(void);
    QStandardItem* currentItem;
#ifdef ENABLE_TREE_VIEW
    void CDevtreeViewTest(void);
#endif
//net
private:
/*
std::vector<std::unique_ptr<int>> ptrsToInts;
ptrsToInts.emplace_back(new int);
*/

    bool creatTCPSerCon(QString &_ip,QString &_port);
    bool creatTCPCltCon(QString &_ip,QString &_port);
    bool creatUDPSerCon(QString &_ip,QString &_port);
    bool creatUDPCltCon(QString &_ip,QString &_port);
    std::function<bool (QString &_ip,QString &_port)>  netConFunc[4];
    int treeActiveConnType;
    void * activeSocket;
};
#endif // NETTOOL_H
