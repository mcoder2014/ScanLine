#include "Polygon.h"
#include <gl/glut.h>
#include "Point.h"
#include <iostream>
#include <QDebug>

using namespace Mcoder;
using std::vector;

Polygon::Polygon()
{
    this->red = this->green = this->blue = 0;       // 初始为红色
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
        qDebug()<<"小于三个点，不是多边形 ";
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
    this->scan();

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

    int ymin = this->min.getY();
    int ymax = this->max.getY();
    int size_edgeTable = ymax - ymin + 1;
    this->sortedEdgeTable.resize(size_edgeTable);       // 设置边表大小

    Point* p_start = this->points[0];
    Point* p_end;
    int size = this->points.size();     // 获取有多少个点

    for(int i = 1; i<size; i++)
    {
        p_end = this->points[i];
        // 第一条边开始
        this->addEdgeToTable(p_start, p_end);
        p_start = p_end;
    }

    p_end = this->points[0];
    this->addEdgeToTable(p_start, p_end);

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
    vector<EdgeS *> edge_active;                                // 新建活动边表
    int y_min = this->min.getY();                               // 获得扫描区域的最低端
    int size_sortedEdgeTable = this->sortedEdgeTable.size();    // 获得Sorted Edge Table 大小

    for(int i = 0; i < size_sortedEdgeTable; i++)
    {
        int y_scan = y_min + i;                     // 当前扫描的位置

        // 清除已经失效的边
        if(!edge_active.empty())
        {
            vector<EdgeS *>::iterator iter;
            for(iter = edge_active.begin() ; iter < edge_active.end(); iter++)
            {
                EdgeS *temp = *iter;
                if(y_scan > temp->ymax)
                {
                   edge_active.erase(iter);
                    // 防止删除一个点以后，内存位置发生改变，或者删除了最后一个点，导致出现异常
                    if(!edge_active.empty())
                        iter = edge_active.begin();     // 从头重新扫描
                    else
                        break;
                }
            }
        }

        // 将新的线段加入到边表中
        if(this->sortedEdgeTable[i] != NULL)
        {
            vector<EdgeS *> *temp = this->sortedEdgeTable[i];
            int size_temp = temp->size();
            for(int i = 0; i < size_temp; i++)
            {
                edge_active.push_back((*temp)[i]);
            }
        }

        // 画当前扫描线
        this->printScanLine(edge_active, y_scan);   // 画扫描线

    }

    this->printHorizontalLine(this->edge_horizontal);// 画水平线

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

/**
 * @Author Chaoqun
 * @brief  设置颜色
 * @param  QColor
 * @return void
 * @date   2017/04/10
 */
void Polygon::setColor(QColor color)
{
    this->red = color.redF();
    this->green = color.greenF();
    this->blue = color.blueF();
}

/**
 * @Author Chaoqun
 * @brief  添加边到排序边表
 * @param  Point* p_start;
 * @param  Point* p_end;
 * @return 返回值
 * @date   2017/04/09
 */
void Polygon::addEdgeToTable(Point *p_start, Point *p_end)
{
    // 判断哪个点在上方
    Point * p_up, *p_down;
    if(p_start->getY() == p_end->getY() )
    {
        // 水平边不加入数组中，加入水平边表中单独处理
        this->edge_horizontal.push_back(new Edge(*p_start, *p_end));
        return;
    }
    else if(p_start->getY() > p_end->getY())
    {
        // p_start 点在上方
        p_up = p_start;
        p_down = p_end;
    }
    else if(p_start->getY() < p_end->getY())
    {
        // p_end 点在上方
        p_up = p_end;
        p_down = p_start;
    }

    // 获得EdgeS数据的重要部分
    double dx = 1.0 * (p_up->getX() - p_down->getX()) /
            (p_up->getY() - p_down->getY());        // 斜率的倒数
    int y_min = (int)p_down->getY();                // 线段最低端y值
    double xi = p_down->getX();                     // 最下端x值
    int y_max = p_up->getY();                       // 线段最顶端 y值

    // ----------------------每条边 y方向上缩短一点
    xi = xi + dx;
    y_min = y_min + 1;

    int y_id = y_min - this->min.getY();        // 应该插入表中的位置
    vector<EdgeS *> * list_temp = this->sortedEdgeTable[y_id];
    if(list_temp == NULL)
    {
        // 如果这个队列为空的话，新建队列
        this->sortedEdgeTable[y_id] = list_temp
                = new vector<EdgeS *>();      // 新建队列
    }

    list_temp->push_back(new EdgeS(xi, dx, y_max));     // 将EdgeS插入到队列中
}

/**
 * @Author Chaoqun
 * @brief  画扫描线
 * @param  vector<EdgeS *> activeEdgeTable; 活动边表
 * @param  int y;       // y
 * @return 返回值
 * @date   2017/04/09
 */
void Polygon::printScanLine(vector<EdgeS *> activeEdgeTable, int y)
{
    if(activeEdgeTable.empty()){
        qDebug() << "未画扫描线,y="<<y;
        return;
    }

    list<double> intersection;  // 交点

    vector<EdgeS*>::iterator iter_activeEdge;           // 迭代器
    for(iter_activeEdge = activeEdgeTable.begin();
        iter_activeEdge < activeEdgeTable.end();
        iter_activeEdge++)
    {
        EdgeS *edge_temp = *iter_activeEdge;            // 遍历每条边
        double xi = edge_temp->xi;                      // 获取当前 x坐标
        edge_temp->xi = edge_temp->xi + edge_temp->dx;  // 计算下一次的Xi坐标
        intersection.push_back(xi);                     // 加入相交队列
    }

    intersection.sort();        // 对交点排序

    list<double >::iterator iter = intersection.begin();        // 迭代器
    while(iter != intersection.end())
    {
        double left = *iter;            // 左交点
        iter++;
        if(iter == intersection.end())
        {
            qDebug() << "交点个数为奇数个,交点个数： "<< activeEdgeTable.size()
                     <<",x:"<<left<<",y:"<<y;
            break;
        }
        double right = *iter;           // 右交点
        iter++;

        //glColor3d(1.0,0.0,0.0);         // 设置颜色
        glColor3d(this->red, this->green, this->blue);  // 设置颜色
// BUG!!!
//        glBegin(GL_LINES);
//            glVertex2i((int)(left),y);
//            glVertex2i((int)(right),y);
//        glEnd();
        // 画线
        glBegin(GL_POINTS);

        if(left==right) // 如果两条线是重合的，会填一条线
        {
            glEnd();
            return;
        }

        for(int i =left; i <= right; i++)
            glVertex2i(i,y);
        glEnd();

    }

}

void Polygon::printHorizontalLine(vector<Edge *> edgeHorizontal)
{
    if(edgeHorizontal.empty())
    {
        return;
    }

    vector<Edge *>::iterator iter = edgeHorizontal.begin();

    while(iter != edgeHorizontal.end())
    {
        Edge* edge_temp= *iter;     // 获得水平边
        glColor3d(this->red, this->green, this->blue);  // 设置颜色
//        glBegin(GL_LINES);
//           glVertex2i(edge_temp->getStart()->getX(),
//                      edge_temp->getStart()->getY());
//           glVertex2i(edge_temp->getEnd()->getX(),
//                      edge_temp->getEnd()->getY());
//        glEnd();
        int left = edge_temp->getStart()->getX();
        int right = edge_temp->getEnd()->getX();
        int y = edge_temp->getStart()->getY();

        glBegin(GL_POINTS);

        if(left==right) // 如果两条线是重合的，会填一条线
        {
            glEnd();
            return;
        }

        for(int i =left; i <= right; i++)
            glVertex2i(i,y);
        glEnd();

        iter++;
    }
}
