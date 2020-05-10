#include "codecDev.h"
#include "ui_codecDev.h"

codecDev::codecDev(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::codecDev)
{
    ui->setupUi(this);
}

codecDev::~codecDev()
{
    delete ui;
}

