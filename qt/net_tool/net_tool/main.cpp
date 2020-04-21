#include "netTool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    netTool w;
    w.show();

    return a.exec();
}
