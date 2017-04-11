#include "mainwindow.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include "iopolygon.h"
#include <QDebug>

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

    this->widget = new CustomWidget(this);
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

    // 滑动条
    if(this->scale_slider != NULL)
    {
        delete this->scale_slider;
        this->scale_slider = NULL;
    }

    // 显示器
    if(this->scale_edit != NULL)
    {
        delete this->scale_edit;
        this->scale_edit = NULL;
    }

    if(this->scale_label != NULL)
    {
        delete this->scale_label;
        this->scale_label = NULL;
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
    //list.append(this->modesAction);
    //this->editMenu->addAction(this->modesAction);

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
    //list.append(this->fillAction);
    //this->editMenu->addAction(this->fillAction);

    this->colorAction = new QAction(QIcon(":/icon/source/color.png"),QObject::tr("Color"),this);
    this->colorAction->setStatusTip(QObject::tr("Change the color for next polygon"));
    list.append(this->colorAction);
    this->editMenu->addAction(this->colorAction);

    this->aboutAction = new QAction(tr("About Qt"),this);
    this->aboutAction->setStatusTip(tr("Some important things about Qt application."));
    this->aboutMenu->addAction(this->aboutAction);

    this->toolBar->addActions(list);        // 添加按钮到工具栏

    // label用来提示本部分的缩放功能
    this->scale_label = new QLabel(tr("Scale:"));

    // 进度条用来控制widget缩放比例
    this->scale_slider = new QSlider(Qt::Horizontal);
    this->scale_slider->setMinimum(1);          // 不能为0
    this->scale_slider->setMaximum(50);
    this->scale_slider->setValue(10);           // 设置初始倍数为 1
    this->scale_slider->setSingleStep(1);       // 设置间隔为 1
    // 设置大小
    this->scale_slider->setMinimumWidth(50);
    this->scale_slider->setMaximumWidth(200);

    // 显示器
    this->scale_edit = new QLineEdit(tr("1.0"));
    this->scale_edit->setReadOnly(true);            // 设置只读不让别人手动输入
    // 设置大小
    this->scale_edit->setMinimumWidth(20);
    this->scale_edit->setMaximumWidth(50);

    this->toolBar->addWidget(this->scale_label);
    this->toolBar->addWidget(this->scale_edit);
    this->toolBar->addWidget(this->scale_slider);

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
    connect(this->polygonAction, &QAction::triggered,
            this,&MainWindow::drawPolygon);              // 切换画多边形模式

    // 绑定的是widget ，所以widget换新的了，应该解除绑定并重新绑定
    connect(this->backAction, &QAction::triggered,
            this->widget,&CustomWidget::backPolygon);    // 删除上一步
    connect(this->cleanAction,&QAction::triggered,
            this->widget,&CustomWidget::cleanPolygons);  // 清空所有多边形

    connect(this->colorAction,&QAction::triggered,
            this,&MainWindow::setFillColor);             // 设置下一个多边形的填充颜色

    connect(this->fillAction,&QAction::triggered,
            this,&MainWindow::test);
    connect(this->modesAction,&QAction::triggered,
            this,&MainWindow::test);

    connect(this->saveAction,&QAction::triggered,
            this,&MainWindow::saveFile);                   // 读取文件
    connect(this->openAction,&QAction::triggered,
            this,&MainWindow::loadFile);                   // 保存文件

    connect(this->aboutAction,&QAction::triggered,
            this,&MainWindow::aboutQt);


    // 缩放画布倍数
    connect(this->scale_slider,SIGNAL(valueChanged(int)),
            this,SLOT(setLineEditValue(int)));
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
    delete this->aboutAction;
}

/**
 * @Author Chaoqun
 * @brief  设置多边形填充颜色
 * @param  void
 * @return void
 * @date   2017/04/10
 */
void MainWindow::setFillColor()
{
    QColor color = QColorDialog::getColor();
    if(this->widget != NULL)
        this->widget->setColor(color);
}

/**
 * @Author Chaoqun
 * @brief  调整
 * @param  参数
 * @date   2017/04/09
 */
void MainWindow::setLineEditValue(int value)
{
    QString str;
    this->scale_edit->setText(str.setNum(value/10.0, 'f' , 2));
    if(this->widget!=NULL)
    {
        this->widget->resizeGL(value/10.0);
    }
    else
    {
        qDebug("this.widget 为空");
    }
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
         disconnect(this->backAction, &QAction::triggered,
                 this->widget,&CustomWidget::backPolygon);    // 删除上一步
         disconnect(this->cleanAction,&QAction::triggered,
                 this->widget,&CustomWidget::cleanPolygons);  // 清空所有多边形

         delete this->widget;
         this->widget = NULL;
     }

     this->widget  = new CustomWidget(this);    // 新建widget
     this->setCentralWidget(this->widget);
     delete temp;

     if(this->scale_slider != NULL)
     {
         this->scale_slider->setValue(10);  // 设置初始值
     }

     //this->connectAction();     // 重新建立连接
     connect(this->backAction, &QAction::triggered,
             this->widget,&CustomWidget::backPolygon);    // 删除上一步
     connect(this->cleanAction,&QAction::triggered,
             this->widget,&CustomWidget::cleanPolygons);  // 清空所有多边形

}

/**
 * @Author Chaoqun
 * @brief  点击开始绘制多边形
 * @param  参数
 * @date   2017/04/07
 */
void MainWindow::drawPolygon()
{
    if(this->widget != NULL)
    {
        if(this->widget->modeFlag == 0)
        {
            // 提醒用户，切换为绘制多边形
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this,
                            tr("Information"),
                            tr("You have turned the mode to 'Draw Polygons'!"),
                                                 QMessageBox::Ok);
            this->widget->modeFlag = 1;     // 设置为修改
        }
        else if(this->widget->modeFlag == 1)
        {
            // 提醒用户，切换为不绘制多边形
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this,
                            tr("Information"),
                            tr("You have turned the mode to 'Dont't Draw'!"),
                                                 QMessageBox::Ok);
            this->widget->modeFlag = 0;     // 设置为修改
        }
        else if(this->widget->modeFlag == 2)
        {
            // 提醒用户，完成当前多边形
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this,
                            tr("Warning"),
                            tr("Please finish your drawing polygon first! \n Add a new point by left clicking your mouse! \n Finish it by right clicking your mouse!"),
                                                 QMessageBox::Ok);
            //this->widget->modeFlag = 0;     // 设置为修改
        }

    }
}

/**
 * @Author Chaoqun
 * @brief  将画板保存到文件
 * @param  void
 * @return void
 * @date   2017/04/10
 */
void MainWindow::saveFile()
{
//    QString fileName = QFileDialog::getOpenFileName(this,
//         tr("Save Canvas"), "", tr("json file (*.json)"));
    QFileDialog * fileDialog = new QFileDialog(this);           // 新建一个QFileDialog
    fileDialog->setWindowIcon(QIcon(":/icon/source/save.png")); // 设置保存文件图标
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);         // 设置对话框为保存文件类型
    fileDialog->setFileMode(QFileDialog::AnyFile);              // 设置文件对话框能够显示任何文件
    fileDialog->setViewMode(QFileDialog::Detail);               // 文件以细节形式显示出来
    fileDialog->setWindowTitle(tr("Save the canvas content as a JSON file"));

    fileDialog->setNameFilter(tr("JSON files(*.json)"));            // 设置文件过滤器
    if(fileDialog->exec() == QDialog::Accepted)
    {
        QString path = fileDialog->selectedFiles()[0];      // 用户选择文件名
        qDebug() << path;

        vector<Mcoder::Polygon *> * polygons = this->widget->getPolygons();
        IOpolygon io(path);
        io.writeFile(polygons);
    }


}

/**
 * @Author Chaoqun
 * @brief  读取目标文件
 * @param  void
 * @return void
 * @date   2017/04/10
 */
void MainWindow::loadFile()
{
    QFileDialog * fileDialog = new QFileDialog(this);           // 新建一个QFileDialog
    fileDialog->setWindowIcon(QIcon(":/icon/source/open.png")); // 设置打开文件图标
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);         // 设置对话框为打开文件类型
    fileDialog->setFileMode(QFileDialog::ExistingFile);         // 设置文件对话框能够存在的文件
    fileDialog->setViewMode(QFileDialog::Detail);               // 文件以细节形式显示出来
    fileDialog->setNameFilter(tr("JSON files(*.json)"));            // 设置文件过滤器
    fileDialog->setWindowTitle(tr("Open A JSON file for this canvas"));

    if(fileDialog->exec() == QDialog::Accepted)
    {
        QString path = fileDialog->selectedFiles()[0];      // 用户选择文件名
        qDebug() << path;

        vector<Mcoder::Polygon *> * polygons = NULL;
        IOpolygon io(path);
        //io.writeFile(polygons);
        polygons = io.readFile();
        if(polygons == NULL)
        {
            qDebug() << "打开文件失败";
            return;
        }

        if(this->widget!= NULL)
        {
            this->widget->setPolygons(polygons);
            this->widget->needUpdate();
        }
    }

}

/**
 * @Author Chaoqun
 * @brief  关于QT
 * @param  void
 * @return void
 * @date   2017/04/11
 */
void MainWindow::aboutQt()
{
    QMessageBox mb(this);
    mb.aboutQt(this,tr("关于Qt"));
}
