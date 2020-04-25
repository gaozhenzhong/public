#include "netTool.h"
#include "ui_netTool.h"
#include "muduo/base/AsyncLogging.h"
#include "muduo/base/Logging.h"
#include<QDebug>
#include<iostream>
#include<QStandardItemModel>

netTool::netTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::netTool)
{
    ui->setupUi(this);
#ifdef ENABLE_TREE_VIEW
    CDevtreeViewTest();
#else
    CDevtreeViewInit();
#endif

}

netTool::~netTool()
{
    delete ui;
}


void netTool::on_conButton_clicked()
{
    conURL = ui->connIfoEdit->text();
    //LOG_INFO<<conURL.toStdString();   //nead file.pro add CONFIG += console
    //qDebug()<<conURL;
    //ui->recBrowser->insertPlainText(conURL);
    ui->recBrowser->append(conURL);
    ui->recBrowser->moveCursor(QTextCursor::End);
}

QStandardItem *netTool::getItem(QStandardItemModel *model, QString s)
{
    QStandardItem *getitem = NULL;
    if(!model->hasChildren())//判断是否有孩子,没有则返回0
        return NULL;
    QList<QStandardItem*> list = model->findItems(s);
    qDebug() << tr("list is %1").arg(list.length());
    if(list.length() == 0)//如果链表长度为0，即没找到文本为s的条目
    {
        //将搜索子条目是否存在文本为s的条目
        for(int i = 0;i < model->rowCount()&& getitem == NULL;i++)//遍历model下的所有条目,如果getitem有获得对象，则退出循环
        {
            getitem = getItem(model->item(i),s);//寻找第i行条目下的子条目列中是否存在文本为s的条目。
        }
    }
    else
    {
        return list.at(0);
    }
    return getitem;
}

QStandardItem *netTool::getItem(QStandardItem *item, QString s)
{
    if(item == NULL)
        return NULL;
    qDebug() << tr("fine %1").arg(item->text());
    QStandardItem *getitem = NULL;
    if(item->text().compare(s) == 0)
        return item;
    if(!item->hasChildren())//判断是否有孩子,没有则返回0
        return NULL;
    for(int i = 0;i < item->rowCount() && getitem == NULL;i++)//遍历item下所有子条目，若果getitme有获得对象，则退出循环
    {
        QStandardItem * childitem = item->child(i);
        getitem = getItem(childitem,s);//寻找这个子条目的所有子条目是否存在文本为s的条目。
    }
    return getitem;
}
void netTool::CDevtreeViewInit()
{
    //treeview初始化
    model = new QStandardItemModel(ui->CDevtreeView);//创建模型
    ui->CDevtreeView->setModel(model);//导入模型
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("设备名")<<QStringLiteral("信息1")<<QStringLiteral("信息2"));
}
void netTool::CDevtreeViewTest()
{
//https://blog.csdn.net/fangjiaze444/article/details/81569881
    //treeview初始化
    model = new QStandardItemModel(ui->CDevtreeView);//创建模型
    ui->CDevtreeView->setModel(model);//导入模型
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("设备名")<<QStringLiteral("信息1")<<QStringLiteral("信息2"));
    //创建题目
    model->setItem(0,0,new QStandardItem(tr("item two")));//0,0坐标值
        model->item(0)->appendRow(new QStandardItem(tr("item four")));
    model->setItem(2,0,new QStandardItem(tr("item three")));
    //通过名字添加子项
    QList<QStandardItem*> list = model->findItems(tr("item two"));
    for(int i = 0;i<list.length();i++)
    {
        qDebug() << tr("list has ").append(list.at(i)->text());//打印该条目的文本
        //item变量指向这个Item two这个对象
        QStandardItem* item = list.at(i);
        /*参数1：item-row()是获取在上一级model或条目下自己所在的行号
        参数2: 1  是第1列，从第0列开始计数，故是相关信息1下的条目列
        参数3： 是创建一个对象,文本信息是item two msg*/
        model->setItem(item->row(),1,new QStandardItem(tr("item two msg")));
    }
    QStandardItem * getitem = getItem(model,tr("item four"));
    getitem->parent()->setChild(getitem->row(),1,new QStandardItem(tr("item four msg")));
}
