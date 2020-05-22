#include "uiTest.h"
#include "ui_uiTest.h"

uiTest::uiTest(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::uiTest)
{
    ui->setupUi(this);
}

uiTest::~uiTest()
{
    delete ui;
}

