#ifndef NETLINUXTOOL_H
#define NETLINUXTOOL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class netLinuxTool; }
QT_END_NAMESPACE

class netLinuxTool : public QMainWindow
{
    Q_OBJECT

public:
    netLinuxTool(QWidget *parent = nullptr);
    ~netLinuxTool();

private:
    Ui::netLinuxTool *ui;
};
#endif // NETLINUXTOOL_H
