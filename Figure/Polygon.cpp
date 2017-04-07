#include "Polygon.h"
#include <gl/glut.h>
#include "Point.h"

using namespace Mcoder;
using std::vector;

Polygon::Polygon()
{

}

Polygon::Polygon(vector<Point *>& points)
{
    this->points.clear();   // 清空
    this->points.insert(this->points.end(),points.begin(),points.end());
}

/**
 * @Author Chaoqun
 * @brief  插入一个新的点
 * @param  int x, int y 点坐标
 * @date   2017/04/06
 */
void Polygon::push(int x, int y)
{
    this->points.push_back(new Point(x, y));   // 插入一个点
}

/**
 * @Author Chaoqun
 * @brief  获取多边形的点
 * @date   2017/04/06
 */
vector<Point *> *Polygon::getPoints()
{
    return &this->points;
}

void Polygon::setPoints(vector<Point *>& points)
{
    this->points.clear();   // 清空
    this->points.insert(this->points.end(),points.begin(),points.end());
}

// 获得该多边形有多少个顶点
int Polygon::getSize()
{
    return this->points.size();
}

/**
 * @Author Chaoqun
 * @brief  获得第几个点
 * @param  int i 第i个点
 * @date   2017/04/06
 */
Point* Polygon::getPoint(int i)
{
    if(i >= this->points.size() || i < 0)
    {
        return NULL;
    }

    return this->points[i];

}

Point *Polygon::getEndPoint()
{
    return this->points.back();
}

/**
 * @Author Chaoqun
 * @brief  绘制多边形
 * @param  int line_strip = 0 -> 折线，首尾不相连 1-> 多边形，首尾相连
 * @date   2017/04/07
 */
void Polygon::paint(int line_strip)
{
    if(line_strip == 1)
    {
        glBegin(GL_LINE_STRIP);
            for(int i = 0; i < this->points.size(); i++)
            {
                glVertex2f((this->points[i])->getX(),(this->points[i])->getY());
            }

        glEnd();
    }
    else if(line_strip == 0)
    {
        glBegin(GL_LINE_LOOP);
            for(int i = 0; i < this->points.size(); i++)
            {
                glVertex2f((this->points[i])->getX(),(this->points[i])->getY());
            }

        glEnd();
    }
}

/**
 * @Author Chaoqun
 * @brief  扫描线填充算法
 * @date   2017/04/07
 */
void Polygon::scanLine()
{
}
