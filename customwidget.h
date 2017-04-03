#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QMenu>
#include <QToolBar>
#include <QWidget>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = 0);
    ~CustomWidget();

signals:

public slots:

private:

    void initUI();              // 初始化界面元素
    void deleteUI();            // 释放UI元素内存空间

    QToolBar *toolBar;




};

#endif // CUSTOMWIDGET_H
