#ifndef CODECSERVER_H
#define CODECSERVER_H

#include <QWidget>
#include"muduo/base/TimeZone.h"
#include "server/socketServer.h"
#include <iostream>
//#define SOCKT_SERVER_CLASS
QT_BEGIN_NAMESPACE
namespace Ui { class codecServer; }
QT_END_NAMESPACE

class codecServer : public QWidget
{
    Q_OBJECT

public:
    codecServer(QWidget *parent = nullptr);
    ~codecServer();

private slots:
    void on_serverStartButton_clicked();

private:
    Ui::codecServer *ui;
    int serverPort;
    QString serverIP;
    std::unique_ptr<muduo::TimeZone> uiLogTimeZone;
#ifdef SOCKT_SERVER_CLASS
    socketServer* scktServer;
#endif
};

#endif // CODECSERVER_H
