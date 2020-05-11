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
#include <QtWidgets/QComboBox>
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
    QTextBrowser *textBrowser;
    QWidget *devInfo;
    QComboBox *serModeComboBox;

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
        portLabel->setGeometry(QRect(440, 10, 67, 17));
        PortLineEdit = new QLineEdit(codecServer);
        PortLineEdit->setObjectName(QString::fromUtf8("PortLineEdit"));
        PortLineEdit->setGeometry(QRect(500, 10, 113, 25));
        serverStartButton = new QPushButton(codecServer);
        serverStartButton->setObjectName(QString::fromUtf8("serverStartButton"));
        serverStartButton->setGeometry(QRect(640, 10, 89, 25));
        tabWidget = new QTabWidget(codecServer);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(290, 60, 491, 521));
        log = new QWidget();
        log->setObjectName(QString::fromUtf8("log"));
        textBrowser = new QTextBrowser(log);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(0, 0, 491, 471));
        tabWidget->addTab(log, QString());
        devInfo = new QWidget();
        devInfo->setObjectName(QString::fromUtf8("devInfo"));
        tabWidget->addTab(devInfo, QString());
        serModeComboBox = new QComboBox(codecServer);
        serModeComboBox->addItem(QString());
        serModeComboBox->addItem(QString());
        serModeComboBox->setObjectName(QString::fromUtf8("serModeComboBox"));
        serModeComboBox->setGeometry(QRect(290, 10, 86, 25));

        retranslateUi(codecServer);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(codecServer);
    } // setupUi

    void retranslateUi(QWidget *codecServer)
    {
        codecServer->setWindowTitle(QCoreApplication::translate("codecServer", "codecServer", nullptr));
        portLabel->setText(QCoreApplication::translate("codecServer", "PORT \357\274\232", nullptr));
        serverStartButton->setText(QCoreApplication::translate("codecServer", "ServerStart", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(log), QCoreApplication::translate("codecServer", "Log", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(devInfo), QCoreApplication::translate("codecServer", "DevInfo", nullptr));
        serModeComboBox->setItemText(0, QCoreApplication::translate("codecServer", "Mode1", nullptr));
        serModeComboBox->setItemText(1, QString());

    } // retranslateUi

};

namespace Ui {
    class codecServer: public Ui_codecServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODECSERVER_H
