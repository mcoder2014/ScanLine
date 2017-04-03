#include "customwidget.h"

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
    this->initUI();     // 初始化UI
}

CustomWidget::~CustomWidget()
{
    this->deleteUI();       // 释放内存空间
}


void CustomWidget::initUI()
{
}


void CustomWidget::deleteUI()
{

}
