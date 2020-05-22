/********************************************************************************
** Form generated from reading UI file 'codecServer.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODECSERVER_H
#define UI_CODECSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_codecServer
{
public:
    QTreeView *devTreeView;
    QLabel *portLabel;
    QLineEdit *PortLineEdit;
    QPushButton *serverStartButton;
    QTabWidget *tabWidget;
    QWidget *log;
    QTextBrowser *logTextBrowser;
    QWidget *devInfo;
    QLabel *IpLabel;
    QLineEdit *IpLineEdit;

    void setupUi(QWidget *codecServer)
    {
        if (codecServer->objectName().isEmpty())
            codecServer->setObjectName(QString::fromUtf8("codecServer"));
        codecServer->resize(800, 600);
        devTreeView = new QTreeView(codecServer);
        devTreeView->setObjectName(QString::fromUtf8("devTreeView"));
        devTreeView->setGeometry(QRect(10, 10, 256, 571));
        portLabel = new QLabel(codecServer);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));
        portLabel->setGeometry(QRect(500, 10, 67, 17));
        PortLineEdit = new QLineEdit(codecServer);
        PortLineEdit->setObjectName(QString::fromUtf8("PortLineEdit"));
        PortLineEdit->setGeometry(QRect(550, 10, 113, 25));
        serverStartButton = new QPushButton(codecServer);
        serverStartButton->setObjectName(QString::fromUtf8("serverStartButton"));
        serverStartButton->setGeometry(QRect(680, 10, 89, 25));
        tabWidget = new QTabWidget(codecServer);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(290, 60, 491, 521));
        log = new QWidget();
        log->setObjectName(QString::fromUtf8("log"));
        logTextBrowser = new QTextBrowser(log);
        logTextBrowser->setObjectName(QString::fromUtf8("logTextBrowser"));
        logTextBrowser->setGeometry(QRect(0, 0, 491, 471));
        tabWidget->addTab(log, QString());
        devInfo = new QWidget();
        devInfo->setObjectName(QString::fromUtf8("devInfo"));
        tabWidget->addTab(devInfo, QString());
        IpLabel = new QLabel(codecServer);
        IpLabel->setObjectName(QString::fromUtf8("IpLabel"));
        IpLabel->setGeometry(QRect(310, 10, 31, 17));
        IpLineEdit = new QLineEdit(codecServer);
        IpLineEdit->setObjectName(QString::fromUtf8("IpLineEdit"));
        IpLineEdit->setGeometry(QRect(342, 10, 141, 25));

        retranslateUi(codecServer);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(codecServer);
    } // setupUi

    void retranslateUi(QWidget *codecServer)
    {
        codecServer->setWindowTitle(QCoreApplication::translate("codecServer", "codecServer", nullptr));
        portLabel->setText(QCoreApplication::translate("codecServer", "PORT \357\274\232", nullptr));
        PortLineEdit->setText(QCoreApplication::translate("codecServer", "8001", nullptr));
        serverStartButton->setText(QCoreApplication::translate("codecServer", "ServerStart", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(log), QCoreApplication::translate("codecServer", "Log", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(devInfo), QCoreApplication::translate("codecServer", "DevInfo", nullptr));
        IpLabel->setText(QCoreApplication::translate("codecServer", "IP :", nullptr));
        IpLineEdit->setText(QCoreApplication::translate("codecServer", "127.0.0.1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class codecServer: public Ui_codecServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODECSERVER_H
