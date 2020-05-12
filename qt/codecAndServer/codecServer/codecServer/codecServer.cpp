#include "codecServer.h"
#include "ui_codecServer.h"
#include "server/socketServer.h"
#include "muduo/base/Logging.h"
codecServer::codecServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::codecServer)
{
//init muduo::Logger
    uiLogTimeZone = std::unique_ptr<muduo::TimeZone>(new muduo::TimeZone(8*3600,"china"));
    muduo::Logger::setLogLevel(muduo::Logger::TRACE);
    muduo::Logger::setTimeZone(*uiLogTimeZone.get());
    ui->setupUi(this);
}

codecServer::~codecServer()
{
    delete ui;
}


void codecServer::on_serverStartButton_clicked()
{
    bool bRst;
    serverPort = ui->PortLineEdit->text().toInt(&bRst);
    serverIP = ui->IpLineEdit->text();
    socketServer sckServer(serverIP.toStdString(),serverPort);
    sckServer.threadStart();
    ui->logTextBrowser->append(QString("%1 : %2 : creat success").arg(serverIP).arg(serverPort));
    ui->serverStartButton->setText("stopServer");
}
