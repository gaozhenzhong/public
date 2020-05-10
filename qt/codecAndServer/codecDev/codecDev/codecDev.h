#ifndef CODECDEV_H
#define CODECDEV_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class codecDev; }
QT_END_NAMESPACE

class codecDev : public QDialog
{
    Q_OBJECT

public:
    codecDev(QWidget *parent = nullptr);
    ~codecDev();

private:
    Ui::codecDev *ui;
};
#endif // CODECDEV_H
