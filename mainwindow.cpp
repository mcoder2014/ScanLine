#include "mainwindow.h"

#include <QDesktopWidget>
#include<QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->initUI();     // 初始化界面
}

MainWindow::~MainWindow()
{
    this->deleteUI();       // 释放界面内存空间
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
