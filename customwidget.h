#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QtOpenGL/qgl.h>
#include <QWidget>
#include <vector>
#include "Figure/Polygon.h"


using namespace Mcoder;
using std::vector;        // 命名空间

class CustomWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = 0);
    ~CustomWidget();

protected:
   void initializeGL();
   void paintGL();
   void resizeGL(int width, int height);

private:
    vector<Mcoder::Polygon*> polygons;
    Mcoder::Polygon * temp;             // 正在画的，仍为画完的多边形



};

#endif // CUSTOMWIDGET_H
