#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QGLWidget>
#include <QWidget>
#include <vector>
#include "Polygon.h"

using namespace std::vector;        // 命名空间
using namespace Mcoder;             // 自定义命名空间

class CustomWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = 0);
    ~CustomWidget();

protected:
   void initializeGL();
   void paintGL();
   void resizeGL(int w, int h);

private:
    vector<Polygon*> polygons;
    Polygon * temp;             // 正在画的，仍为画完的多边形



};

#endif // CUSTOMWIDGET_H
