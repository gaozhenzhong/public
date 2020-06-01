#ifndef CODECDEV_H
#define CODECDEV_H

#include <QDialog>
#include <QTcpSocket>
#include<memory>
#include<vector>
QT_BEGIN_NAMESPACE
namespace Ui { class codecDev; }
QT_END_NAMESPACE

class codecDev : public QDialog
{
    Q_OBJECT
private:
    class orderData
    {
    public:
        orderData(char id,char* _data,char _size);

        const char *orderHeadStr     = "FF55FF55";
        const char orderHeadLen      = 8;
        const int  orderLenAddr      = 8;
        const int  orderIDAddr       = 9;
        const char orderIDDataAddr   = 10;
        const char *orderTailStr     = "55FF55FF";
        const char orderTailLen      = 8;

        char order_[300];
        int  len_;
    };
public:
    codecDev(QWidget *parent = nullptr);
    ~codecDev();
private slots:
    void on_conPushButton_clicked();
    void on_sendOrderButton_clicked();
private:
    Ui::codecDev *ui;
    QTcpSocket  * tcpSocket;
    bool process_netCmd(QByteArray & _bArray);
};
#endif // CODECDEV_H
