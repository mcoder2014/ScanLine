#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    QToolBar *toolBar;
};

#endif // MAINWINDOW_H
