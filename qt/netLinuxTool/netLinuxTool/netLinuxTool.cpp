#include "netLinuxTool.h"
#include "./ui_netLinuxTool.h"

netLinuxTool::netLinuxTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::netLinuxTool)
{
    ui->setupUi(this);
}

netLinuxTool::~netLinuxTool()
{
    delete ui;
}

