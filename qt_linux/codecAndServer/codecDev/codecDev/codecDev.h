#ifndef CODECDEV_H
#define CODECDEV_H

#include <QDialog>
#include <QTcpSocket>
#include<memory>

QT_BEGIN_NAMESPACE
namespace Ui { class codecDev; }
QT_END_NAMESPACE

class codecDev : public QDialog
{
    Q_OBJECT

public:
    codecDev(QWidget *parent = nullptr);
    ~codecDev();
private slots:
    void on_conPushButton_clicked();
    void on_sendOrderButton_clicked();
private:
    Ui::codecDev *ui;
    std::unique_ptr<QTcpSocket> tcpSocket;
    bool process_netCmd(QByteArray & _bArray);
};
#endif // CODECDEV_H
