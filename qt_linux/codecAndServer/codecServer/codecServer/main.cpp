#include "codecServer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    codecServer w;
    w.show();
    return a.exec();
}
