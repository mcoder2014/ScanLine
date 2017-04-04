#include "customwidget.h"

CustomWidget::CustomWidget(QWidget *parent) : QGLWidget(parent)
{
    this->initUI();     // 初始化UI
}

CustomWidget::~CustomWidget()
{
    this->deleteUI();       // 释放内存空间
}

// 设置初始化内容
void CustomWidget::initializeGL()
{

}

void CustomWidget::paintGL()
{

}

// 重新设置窗口大小
void CustomWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w,(GLint)h);

}



