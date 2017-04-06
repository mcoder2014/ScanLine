#include "mainwindow.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QWidget>
#include <QMenuBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->initUI();     // 初始化界面
    this->initAction();         // 设置动作按钮
    connectAction();            // 绑定 信号槽、动作
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

    this->toolBar = this->addToolBar(tr("Canvas ToolBar"));          // 增加工具栏

    // 增加菜单栏
    this->filesMenu = this->menuBar()->addMenu(tr("File"));
    this->editMenu = this->menuBar()->addMenu(tr("Edit"));
    this->aboutMenu = this->menuBar()->addMenu(tr("About"));

    this->msgLabel = new QLabel;
    this->statusBar()->addWidget(this->msgLabel);

    this->setVisible(true);     // 设置为可见




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

    // 状态栏
    if( this->msgLabel != NULL)
    {
        delete this->msgLabel;
        this->msgLabel = NULL;
    }

}

/**********************************
 * 初始化QAction
 * *******************************/
void MainWindow::initAction()
{
    QList<QAction *> list;

    this->newAction = new QAction(QIcon(":/icon/source/new.png"),QObject::tr("New"),this);
    this->newAction->setStatusTip(QObject::tr("Create new canvas, for your painting!"));                             // 设置提醒
    this->newAction->setShortcut(QKeySequence::New);                                  // 设置快捷键
    list.append(this->newAction);
    this->filesMenu->addAction(this->newAction);

    this->openAction = new QAction(QIcon(":/icon/source/open.png"),QObject::tr("Open"),this);
    this->openAction->setStatusTip(QObject::tr("Open files!"));
    this->openAction->setShortcut(QKeySequence::Open);
    list.append(this->openAction);
    this->filesMenu->addAction(this->openAction);

    this->saveAction = new QAction(QIcon(":/icon/source/save.png"),QObject::tr("Save As"),this);
    this->saveAction->setStatusTip(QObject::tr("Save your painting as the file."));
    this->saveAction->setShortcut(QKeySequence::SaveAs);
    list.append(this->saveAction);
    this->filesMenu->addAction(this->saveAction);

    this->exitAction = new QAction(QIcon(":/icon/source/exit.png"),tr("Exit"),this);
    this->exitAction->setStatusTip(tr("End this program !"));
    this->filesMenu->addSeparator();
    this->filesMenu->addAction(this->exitAction);

    this->cleanAction = new QAction(QIcon(":/icon/source/clean.png"),QObject::tr("Clean"),this);
    this->cleanAction->setStatusTip(QObject::tr("Clean the Canvas as you open it first time."));
    list.append(this->cleanAction);
    this->editMenu->addAction(this->cleanAction);

    this->modesAction = new QAction(QIcon(":/icon/source/modes.png"),QObject::tr("Mode"),this);
    this->modesAction->setStatusTip(QObject::tr("Change the mode to change the way you fill polygons."));
    list.append(this->modesAction);
    this->editMenu->addAction(this->modesAction);

    this->polygonAction = new QAction(QIcon(":/icon/source/polygon.png"),QObject::tr("Polygon"),this);
    this->polygonAction->setStatusTip(QObject::tr("Draw your polygons , start with Left Button, end with right button."));
    list.append(this->polygonAction);
    this->editMenu->addAction(this->polygonAction);

    this->backAction = new QAction(QIcon(":/icon/source/delete.png"),QObject::tr("Undo"),this);
    this->backAction->setStatusTip(QObject::tr("Delete last polygon you draw."));
    list.append(this->backAction);
    this->editMenu->addAction(this->backAction);

    this->fillAction = new QAction(QIcon(":/icon/source/fill.png"),QObject::tr("Fill"),this);
    this->fillAction->setStatusTip(QObject::tr("Fill the polygons"));
    list.append(this->fillAction);
    this->editMenu->addAction(this->fillAction);

    this->colorAction = new QAction(QIcon(":/icon/source/color.png"),QObject::tr("Color"),this);
    this->colorAction->setStatusTip(QObject::tr("Change the color for next polygon"));
    list.append(this->colorAction);
    this->editMenu->addAction(this->colorAction);

    this->toolBar->addActions(list);        // 添加按钮到工具栏

}

/***************************************
 * 连接信号槽
 * ************************************/
void MainWindow::connectAction()
{
    connect(this->exitAction, &QAction::triggered,
            this,&MainWindow::close);                    // 连接退出程序按钮
    connect(this->newAction, &QAction::triggered,
            this, &MainWindow::createNewWidget);         // 创建新画板

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

/**
 * @Author Chaoqun
 * @brief  函数头注释
 * @param  无
 * @date   2017/04/06
 */
void MainWindow::createNewWidget()
{
    QLabel *temp = new QLabel(tr("Wait for minutes ..."));      // 用临时QLabel替换widget
     if(this->widget != NULL)
     {
         this->setCentralWidget(temp);
         delete this->widget;
         this->widget = NULL;
     }

     this->widget  = new CustomWidget(this);    // 新建widget
     this->setCentralWidget(this->widget);
     delete temp;

}
