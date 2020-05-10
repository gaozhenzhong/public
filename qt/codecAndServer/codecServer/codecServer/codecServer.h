#ifndef CODECSERVER_H
#define CODECSERVER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class codecServer; }
QT_END_NAMESPACE

class codecServer : public QWidget
{
    Q_OBJECT

public:
    codecServer(QWidget *parent = nullptr);
    ~codecServer();

private:
    Ui::codecServer *ui;
};
#endif // CODECSERVER_H
