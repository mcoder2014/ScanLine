#include "Polygon.h"
#include <gl/glut.h>
#include "Point.h"
#include <iostream>

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
    this->points.push_back(new Point(x,y));   // 插入一个点
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
    if(this->getSize() < 3)
    {
        // 如果小于三个点，则不是多边形，无法填充
        return ;
    }

    // 确定扫描线的范围
    this->min.copy(*this->points[0]);
    this->max.copy(*this->points[0]);
    int size = this->getSize();

    for(int i = 0; i < size; i++)
    {
        Point * temp = this->points[i];

        if(temp->getX() < min.getX())
        {
            min.setX(temp->getX());
        }
        else if(temp->getX() > max.getX())
        {
            max.setX(temp->getX());
        }

        if(temp->getY() < min.getY())
        {
            min.setY(temp->getY());
        }
        else if(temp->getY() > max.getY())
        {
            max.setY(temp->getY());
        }
    }

    // 确定了扫描线范围 min.y -> max.y
    this->buildEdgeTable();


}


/**
 * @Author Chaoqun
 * @brief  生成边表
 * @return bool
 * @date   2017/04/08
 */
bool Polygon::buildEdgeTable()
{

    if(this->getSize() < 3)
    {
        return false ;     // 三条边算不上多边形
    }

    this->sortedEdgeTable.clear();  // 清空边表
    this->edge_horizontal.clear();  // 清空水平边

    int ymin = (double)(this->min.getY() - 1);
    int ymax = (double)(this->max.getY() + 1);
    int size_edgeTable = ymax - ymin;
    this->sortedEdgeTable.resize(size_edgeTable);       // 设置边表大小

    Point* p_start = this->points[0];
    Point* p_end;
    int size = this->getSize();

    for(int i = 1; i<size; i++)
    {
        p_end = this->points[i];
        // 第一条边开始
        Point * p_up, *p_down;
        if(p_start->getY() > p_end->getY())
        {
            p_up = p_start;
            p_down = p_end;
        }
        else if(p_start->getY() < p_end->getY())
        {
            p_up = p_end;
            p_down = p_start;
        }
        else if(p_start->getY() == p_end->getY())
        {
            // 水平边不加入数组中，加入水平边表中单独处理
            this->edge_horizontal.push_back(new Edge(*p_start, *p_end));
            continue;
        }

        double dx = (p_up->getX() - p_down->getX()) /
                (p_up->getY() - p_down->getY());        // 斜率的倒数
        double y_min = p_down->getY();                  // 最小y值
        double xi = p_down->getX();                     // 最小x值
        double y_max = p_up->getY();                    // 最大y值

        // 线段去掉低的那个点
        if(dx > 1||dx < -1)
        {
            // x方向去掉一个点
            if(dx < 0)
            {
                xi = xi - 1;
            }
            else if(dx > 0)
            {
                xi = xi + 1;
            }

        }
        else
        {
            // y方向去掉一个点
            y_min = y_min + 1;
        }

        vector<EdgeS *> * list_temp = this->sortedEdgeTable[(int)(y_min - this->min.getY())];
        if(list_temp == NULL)
        {
            // 如果这个队列为空的话
            this->sortedEdgeTable[(int)(y_min - this->min.getY())] = list_temp
                    = new vector<EdgeS *>();      // 新建队列
        }
        list_temp->push_back(new EdgeS(xi ,dx, y_max));

        p_start = p_end;
    }

    p_end = this->points[0];

    return true;
}

/**
 *@Author Chaoqun
 *@brief  填充
 *@return void
 *@date   2017/04/08
 */
void Polygon::scan()
{
    vector<EdgeS *> edge_active;
    double y_min = this->min.getY();
    int size_sortedEdgeTable = this->sortedEdgeTable.size();

    for(int i = 0; i < size_sortedEdgeTable; i++)
    {
        // 扫描
        if(this->sortedEdgeTable[i] != NULL)
        {
            vector<EdgeS *> *temp = this->sortedEdgeTable[i];
            int size_temp = temp->size();
            for(int i = 0; i < size_temp; i++)
            {
                edge_active.push_back(*temp[i]);
            }
        }

        if(edge_active.size() == 0)
        {
            // 如果队列中无点
            continue;
        }
        int y_scan = (int)y_min + i;    // 当前扫描的行数

    }

}

/**
 * @Author Chaoqun
 * @brief  输出多边形信息
 * @return void
 * @date   2017/04/08
 */
void Polygon::print()
{
    std::cout << "Points:";
    int p_size = this->points.size();
    for(int i = 0; i < p_size; i++)
    {
        (this->points[i])->print();
        std::cout << " ";
    }

}
