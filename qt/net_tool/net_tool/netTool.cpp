#include "netTool.h"
#include "ui_netTool.h"

netTool::netTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::netTool)
{
    ui->setupUi(this);
}

netTool::~netTool()
{

    delete ui;
}
