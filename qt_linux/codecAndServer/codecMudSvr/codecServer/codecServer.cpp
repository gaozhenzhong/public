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
// start ui
    ui->setupUi(this);
}

codecServer::~codecServer()
{
    delete ui;
}


void codecServer::on_serverStartButton_clicked()
{
    bool bRst;
    if(NULL == connServer_)
    {
        serverPort = ui->PortLineEdit->text().toInt(&bRst);
        serverIP = ui->IpLineEdit->text();

        connServer_=new connServer(serverIP.toStdString(),serverPort);

        ui->logTextBrowser->append(QString("%1 : %2 : creat success").arg(serverIP).arg(serverPort));
        ui->serverStartButton->setText("stopServer");
    }
    else
    {
        delete  connServer_;
        connServer_ = NULL;
        ui->serverStartButton->setText("ConnServer");
    }
#ifdef SOCKT_SERVER_CLASS
    bool bRst;
    if(NULL == scktServer)
    {
        serverPort = ui->PortLineEdit->text().toInt(&bRst);
        serverIP = ui->IpLineEdit->text();

        scktServer=new socketServer(serverIP.toStdString(),serverPort);       
        scktServer->threadStart();
        ui->logTextBrowser->append(QString("%1 : %2 : creat success").arg(serverIP).arg(serverPort));
        ui->serverStartButton->setText("stopServer");
    }
    else
    {
        scktServer->threadEnd();
        delete  scktServer;
        scktServer = NULL;
        ui->serverStartButton->setText("ConnServer");
    }
#endif

}
