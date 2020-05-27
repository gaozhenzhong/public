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
    private:
        //std::vector<char> order_{'5','5','F','F','5','5','F','F'};
        char order_;
        int  len;
    };
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
