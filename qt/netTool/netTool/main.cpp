#include "netTool.h"
#include "MuduoTest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MuduoTest muduo;
    netTool w;
    w.show();
    return a.exec();
}
