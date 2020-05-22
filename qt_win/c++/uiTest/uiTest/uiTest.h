#ifndef UITEST_H
#define UITEST_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class uiTest; }
QT_END_NAMESPACE

class uiTest : public QMainWindow
{
    Q_OBJECT

public:
    uiTest(QWidget *parent = nullptr);
    ~uiTest();

private:
    Ui::uiTest *ui;
};
#endif // UITEST_H
