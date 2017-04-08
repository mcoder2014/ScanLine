#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QtOpenGL/qgl.h>
#include <QMouseEvent>
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

    int modeFlag;           // 用来表示当前处于何种状态
    /*
     * 0 无操作
     * 1 绘制多边形-未开始
     * 2 绘制多边形-已开始
     */

    void backPolygon();     // 删除上一个多边形
    void cleanPolygons();   // 清空所有多边形
    float getScale();       // 获得缩放倍数

    void resizeGL(float scale);        // 调整缩放倍数

protected:
   void initializeGL();
   void paintGL();
   void resizeGL(int width, int height);
   void resizeGL(int width, int height, float scale);       // 设置屏幕缩放


private:
    vector<Mcoder::Polygon*> polygons;
    Mcoder::Polygon * temp;             // 正在画的，仍为画完的多边形
    int width,height;                   // 画布的宽和高
    float scale;            // 缩放值
    int mouse_x, mouse_y;    // 用来暂存鼠标
    int pushButton;          //用来暂存点下的鼠标按键 非点击状态给更改为 -1

    void mouseMoveEvent(QMouseEvent *event);        // 鼠标移动事件
    void mousePressEvent(QMouseEvent *event);       // 鼠标点击事件
    void mouseReleaseEvent(QMouseEvent *event);     // 鼠标释放事件

    void convertMouse(QMouseEvent *event);            // 更改坐标


};

#endif // CUSTOMWIDGET_H
