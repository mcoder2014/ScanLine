#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customwidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QSlider>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:


    QMenu * filesMenu;          // 初始化菜单
    QMenu * editMenu;           // 操作菜单
    QMenu * aboutMenu;          // 关于菜单

    QToolBar * toolBar;         // 初始化一个工具栏
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
    QAction * exitAction;       // 退出程序->藏于菜单中

    QAction * aboutAction;      // 关于

    QLabel * scale_label;       // 用来提醒本部分是缩放功能
    QSlider * scale_slider;     // 绘图区缩放比例
    QLineEdit * scale_edit;

    QLabel * msgLabel;          // 添加状态栏

    void test()                // 用来测试信号槽是否通了
    {
        qDebug("信号槽通了");
    }

    void initUI();              // 初始化界面元素
    void deleteUI();            // 释放UI元素内存空间

    void initAction();          // 初始化QAction
    void connectAction();       // 初始化界面后，连接操作
    void deleteAction();        // 释放QAction
    void setFillColor();        // 设置填充颜色



    void createNewWidget();     // 新建画板
    void drawPolygon();         // 切换绘制与未绘制状态
    void saveFile();            // 保存画板到文件
    void loadFile();            // 从文件中读取画板

    void aboutQt();             // 弹出关于QT的相关的


private slots:
    void setLineEditValue(int value);   // 显示放大倍数


};

#endif // MAINWINDOW_H
