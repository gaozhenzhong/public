#include "netTool.h"
#include "ui_netTool.h"
#include "muduo/base/AsyncLogging.h"
#include "muduo/base/Logging.h"
#include<QDebug>
#include<iostream>

netTool::netTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::netTool)
{
    ui->setupUi(this);
}

netTool::~netTool()
{
    delete ui;
}


void netTool::on_conButton_clicked()
{
    conURL = ui->connIfoEdit->text();
    //LOG_INFO<<conURL.toStdString();   //nead file.pro add CONFIG += console
    //qDebug()<<conURL;
    //ui->recBrowser->insertPlainText(conURL);
    ui->recBrowser->append(conURL);
    ui->recBrowser->moveCursor(QTextCursor::End);
}
