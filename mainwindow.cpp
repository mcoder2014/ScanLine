#include "mainwindow.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QAction>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->initUI();     // 初始化界面
    this->initAction();         // 设置动作按钮
}

MainWindow::~MainWindow()
{
    this->deleteUI();       // 释放界面内存空间
    this->deleteAction();
}

/***************************
 * 初始化界面元素
 * 返回值 void
 * ************************/
void MainWindow::initUI()
{
    this->setVisible(false);     // 先设为不可见
    // this->setWindowTitle(QObject::tr("Jiang Chaoqun's Scan Line Polygen Fill"));
    this->setWindowTitle(QObject::tr("江超群的多边形扫描线填充算法"));
    // 设置窗口大小为屏幕中心指定位置
    QDesktopWidget *desktop = QApplication::desktop();

    QRect screenRect = desktop->screenGeometry(desktop->primaryScreen());       // 获取默认系统默认桌面的桌面大小
    float multiple = 3.0/5;
    this->setMinimumSize(multiple*screenRect.width(),
                       multiple*screenRect.height());             // 设置大小为4/5
    this->move(0.5*(1-multiple) * screenRect.width(),
               0.5 * (1 - multiple) * screenRect.height());       // 移动窗口位置

    this->widget = new CustomWidget();
    this->setCentralWidget(widget);         // 将openGL画板放在主窗口中间

    this->setWindowIcon(QIcon(":/icon/source/icon.png"));       // 设置窗口左上角图标



    this->setVisible(true);     // 设置为可见



    this->toolBar = this->addToolBar(tr("新建画布"));
}

/******************************
 * 释放UI元素内存空间
 * ***************************/
void MainWindow::deleteUI()
{
    // 工具栏
    if(this->toolBar != NULL) {
        delete this->toolBar;
        this->toolBar = NULL;
    }

    // 画板
    if(this->widget !=NULL)
    {
        delete this->widget;
        this->widget = NULL;
    }
}

/**********************************
 * 初始化QAction
 * *******************************/
void MainWindow::initAction()
{
    QList<QAction *> list;

    this->newAction = new QAction(QIcon(":/icon/source/new.png"),QObject::tr("新建"));
    this->newAction->setStatusTip(QObject::tr("新建画布 "));                             // 设置提醒
    this->newAction->setShortcut(QKeySequence::New);                                  // 设置快捷键
    list.append(this->newAction);

    this->openAction = new QAction(QIcon(":/icon/source/open.png"),QObject::tr("打开 "));
    this->openAction->setStatusTip(QObject::tr("打开已经保存的文件 "));
    this->openAction->setShortcut(QKeySequence::Open);
    list.append(this->openAction);

    this->saveAction = new QAction(QIcon(":/icon/source/save.png"),QObject::tr("保存 "));
    this->saveAction->setStatusTip(QObject::tr("保存文件到…… "));
    this->saveAction->setShortcut(QKeySequence::SaveAs);
    list.append(this->saveAction);

    this->cleanAction = new QAction(QIcon(":/icon/source/clean.png"),QObject::tr("清空 "));
    this->cleanAction->setStatusTip(QObject::tr("清空画布 "));
    list.append(this->cleanAction);

    this->modesAction = new QAction(QIcon(":/icon/source/modes.png"),QObject::tr("模式 "));
    this->modesAction->setStatusTip(QObject::tr("切换多边形填充模式 "));
    list.append(this->modesAction);

    this->polygonAction = new QAction(QIcon(":/icon/source/polygon.png"),QObject::tr("多边形 "));
    this->polygonAction->setStatusTip(QObject::tr("绘制多边形状态 "));
    list.append(this->polygonAction);

    this->backAction = new QAction(QIcon(":/icon/source/delete.png"),QObject::tr("撤销 "));
    this->backAction->setStatusTip(QObject::tr("删除上一个绘制的多边形 "));
    list.append(this->backAction);

    this->fillAction = new QAction(QIcon(":/icon/source/fill.png"),QObject::tr("填充 "));
    this->fillAction->setStatusTip(QObject::tr("填充多边形 "));
    list.append(this->fillAction);

    this->colorAction = new QAction(QIcon(":/icon/source/color.png"),QObject::tr("颜色 "));
    this->colorAction->setStatusTip(QObject::tr("更换颜色 "));
    list.append(this->colorAction);

    this->toolBar->addActions(list);        // 添加按钮到工具栏

}

void MainWindow::connectAction()
{

}

void MainWindow::deleteAction()
{
    delete this->newAction;
    delete this->openAction;
    delete this->saveAction;
    delete this->cleanAction;
    delete this->modesAction;
    delete this->polygonAction;
    delete this->backAction;
    delete this->fillAction;
    delete this->colorAction;
}
