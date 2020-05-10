#include "codecServer.h"
#include "ui_codecServer.h"

codecServer::codecServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::codecServer)
{
    ui->setupUi(this);
}

codecServer::~codecServer()
{
    delete ui;
}

