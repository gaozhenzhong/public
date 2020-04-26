#ifndef NETTOOL_H
#define NETTOOL_H

#include <QMainWindow>
#include<QStandardItemModel>

#include <iostream>
//#define ENABLE_TREE_VIEW

QT_BEGIN_NAMESPACE
namespace Ui { class netTool; }
QT_END_NAMESPACE

class netTool : public QMainWindow
{
    Q_OBJECT

public:
    netTool(QWidget *parent = nullptr);
    ~netTool();
private slots:
    void on_conButton_clicked();

private:
    Ui::netTool *ui;
   // QStandardItemModel* model;
    std::unique_ptr<QStandardItemModel>  model;
    QStandardItem *getItem(QStandardItemModel *model, QString s);
    QStandardItem *getItem(QStandardItem *item, QString s);
    void CDevtreeViewInit(void);
#ifdef ENABLE_TREE_VIEW
    void CDevtreeViewTest(void);
#endif
};
#endif // NETTOOL_H
