#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customwidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    void initUI();              // 初始化界面元素
    void deleteUI();            // 释放UI元素内存空间

    void initAction();          // 初始化QAction
    void connectAction();       // 初始化界面后，连接操作
    void deleteAction();        // 释放QAction

    QMenu *menu;                // 初始化菜单
    QToolBar *toolBar;          // 初始化一个工具栏
    CustomWidget * widget;      // openGL 画板

    QAction * newAction;        // 新建画面
    QAction * openAction;       // 打开文件
    QAction * saveAction;       // 保存文件
    QAction * cleanAction;      // 清屏
    QAction * modesAction;      // 选择填充模式
    QAction * polygonAction;    // 开始绘制多边形状态
    QAction * backAction;     // 删除上一个多边形
    QAction * fillAction;       // 填充多边形
    QAction * colorAction;      // 切换颜色

};

#endif // MAINWINDOW_H
