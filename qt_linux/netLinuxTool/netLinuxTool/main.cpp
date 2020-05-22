#include "netLinuxTool.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    netLinuxTool w;
    w.show();
    return a.exec();
}
