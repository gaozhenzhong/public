#ifndef NETTOOL_H
#define NETTOOL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class netTool; }
QT_END_NAMESPACE

class netTool : public QMainWindow
{
    Q_OBJECT

public:
    netTool(QWidget *parent = nullptr);
    ~netTool();

private:
    Ui::netTool *ui;
};
#endif // NETTOOL_H
