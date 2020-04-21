#ifndef NETTOOL_H
#define NETTOOL_H

#include <QMainWindow>

namespace Ui {
class netTool;
}

class netTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit netTool(QWidget *parent = nullptr);
    ~netTool();

private:
    Ui::netTool *ui;
};

#endif // NETTOOL_H
