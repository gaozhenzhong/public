/********************************************************************************
** Form generated from reading UI file 'uiTest.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UITEST_H
#define UI_UITEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_uiTest
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *uiTest)
    {
        if (uiTest->objectName().isEmpty())
            uiTest->setObjectName(QString::fromUtf8("uiTest"));
        uiTest->resize(800, 600);
        centralwidget = new QWidget(uiTest);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(320, 190, 75, 23));
        uiTest->setCentralWidget(centralwidget);
        menubar = new QMenuBar(uiTest);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        uiTest->setMenuBar(menubar);
        statusbar = new QStatusBar(uiTest);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        uiTest->setStatusBar(statusbar);

        retranslateUi(uiTest);

        QMetaObject::connectSlotsByName(uiTest);
    } // setupUi

    void retranslateUi(QMainWindow *uiTest)
    {
        uiTest->setWindowTitle(QCoreApplication::translate("uiTest", "uiTest", nullptr));
        pushButton->setText(QCoreApplication::translate("uiTest", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class uiTest: public Ui_uiTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UITEST_H
