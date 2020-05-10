/********************************************************************************
** Form generated from reading UI file 'codecDev.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODECDEV_H
#define UI_CODECDEV_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_codecDev
{
public:
    QLineEdit *IPLineEdit;
    QLabel *IPLabel;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QPushButton *conPushButton;
    QLabel *devNameLabel;
    QPushButton *testPushButton;
    QComboBox *testModecomboBox;
    QTabWidget *tabWidget;
    QWidget *log;
    QTextBrowser *logTextBrowser;
    QWidget *order;
    QLineEdit *sendOrderLineEdit;
    QPushButton *sendOrderButton;
    QComboBox *orderComboBox;
    QLabel *recOrderLabel;
    QTextBrowser *recOrderBrowser;

    void setupUi(QDialog *codecDev)
    {
        if (codecDev->objectName().isEmpty())
            codecDev->setObjectName(QString::fromUtf8("codecDev"));
        codecDev->resize(800, 600);
        IPLineEdit = new QLineEdit(codecDev);
        IPLineEdit->setObjectName(QString::fromUtf8("IPLineEdit"));
        IPLineEdit->setGeometry(QRect(100, 40, 191, 25));
        IPLineEdit->setMaxLength(20);
        IPLabel = new QLabel(codecDev);
        IPLabel->setObjectName(QString::fromUtf8("IPLabel"));
        IPLabel->setGeometry(QRect(40, 40, 21, 17));
        portLabel = new QLabel(codecDev);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));
        portLabel->setGeometry(QRect(320, 40, 67, 17));
        portLineEdit = new QLineEdit(codecDev);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));
        portLineEdit->setGeometry(QRect(390, 40, 181, 25));
        portLineEdit->setMaxLength(10);
        conPushButton = new QPushButton(codecDev);
        conPushButton->setObjectName(QString::fromUtf8("conPushButton"));
        conPushButton->setGeometry(QRect(660, 40, 89, 25));
        devNameLabel = new QLabel(codecDev);
        devNameLabel->setObjectName(QString::fromUtf8("devNameLabel"));
        devNameLabel->setGeometry(QRect(40, 10, 321, 17));
        testPushButton = new QPushButton(codecDev);
        testPushButton->setObjectName(QString::fromUtf8("testPushButton"));
        testPushButton->setGeometry(QRect(660, 80, 89, 25));
        testModecomboBox = new QComboBox(codecDev);
        testModecomboBox->addItem(QString());
        testModecomboBox->addItem(QString());
        testModecomboBox->addItem(QString());
        testModecomboBox->setObjectName(QString::fromUtf8("testModecomboBox"));
        testModecomboBox->setGeometry(QRect(100, 80, 191, 25));
        tabWidget = new QTabWidget(codecDev);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(30, 120, 731, 471));
        log = new QWidget();
        log->setObjectName(QString::fromUtf8("log"));
        logTextBrowser = new QTextBrowser(log);
        logTextBrowser->setObjectName(QString::fromUtf8("logTextBrowser"));
        logTextBrowser->setGeometry(QRect(10, 10, 711, 421));
        tabWidget->addTab(log, QString());
        order = new QWidget();
        order->setObjectName(QString::fromUtf8("order"));
        sendOrderLineEdit = new QLineEdit(order);
        sendOrderLineEdit->setObjectName(QString::fromUtf8("sendOrderLineEdit"));
        sendOrderLineEdit->setGeometry(QRect(180, 10, 391, 25));
        sendOrderButton = new QPushButton(order);
        sendOrderButton->setObjectName(QString::fromUtf8("sendOrderButton"));
        sendOrderButton->setGeometry(QRect(600, 10, 89, 25));
        orderComboBox = new QComboBox(order);
        orderComboBox->addItem(QString());
        orderComboBox->setObjectName(QString::fromUtf8("orderComboBox"));
        orderComboBox->setGeometry(QRect(20, 10, 131, 25));
        recOrderLabel = new QLabel(order);
        recOrderLabel->setObjectName(QString::fromUtf8("recOrderLabel"));
        recOrderLabel->setGeometry(QRect(20, 50, 67, 17));
        recOrderBrowser = new QTextBrowser(order);
        recOrderBrowser->setObjectName(QString::fromUtf8("recOrderBrowser"));
        recOrderBrowser->setGeometry(QRect(20, 80, 691, 351));
        tabWidget->addTab(order, QString());

        retranslateUi(codecDev);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(codecDev);
    } // setupUi

    void retranslateUi(QDialog *codecDev)
    {
        codecDev->setWindowTitle(QCoreApplication::translate("codecDev", "codecDev", nullptr));
        IPLineEdit->setText(QCoreApplication::translate("codecDev", "127.0.0.1", nullptr));
        IPLabel->setText(QCoreApplication::translate("codecDev", "IP :", nullptr));
        portLabel->setText(QCoreApplication::translate("codecDev", "PORT :", nullptr));
        portLineEdit->setText(QCoreApplication::translate("codecDev", "8001", nullptr));
        conPushButton->setText(QCoreApplication::translate("codecDev", "connect", nullptr));
        devNameLabel->setText(QCoreApplication::translate("codecDev", "DevName :", nullptr));
        testPushButton->setText(QCoreApplication::translate("codecDev", "TesTStart", nullptr));
        testModecomboBox->setItemText(0, QCoreApplication::translate("codecDev", "TestMode1", nullptr));
        testModecomboBox->setItemText(1, QCoreApplication::translate("codecDev", "TestMode2", nullptr));
        testModecomboBox->setItemText(2, QCoreApplication::translate("codecDev", "TestMode3", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(log), QCoreApplication::translate("codecDev", "log", nullptr));
        sendOrderButton->setText(QCoreApplication::translate("codecDev", "SendOrder", nullptr));
        orderComboBox->setItemText(0, QCoreApplication::translate("codecDev", "StrOrder", nullptr));

        recOrderLabel->setText(QCoreApplication::translate("codecDev", "recOrder", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(order), QCoreApplication::translate("codecDev", "order", nullptr));
    } // retranslateUi

};

namespace Ui {
    class codecDev: public Ui_codecDev {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODECDEV_H
