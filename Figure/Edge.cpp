#include "Edge.h"
#include <iostream>
using namespace Mcoder;

/**
 * @Author Chaoqun
 * @brief  默认构造函数
 * @date   2017/04/08
 */
Edge::Edge()
{
    this->neg_gradient = 0;
}

/**
 * @Author Chaoqun
 * @brief  构造函数
 * @param  double a_x
 * @param  double a_y
 * @param  double b_x
 * @param  double b_y
 * @date   2017/04/08
 */
Edge::Edge(double a_x, double a_y, double b_x, double b_y)
{
    this->p_start.set(a_x, a_y);
    this->P_end.set(b_x, b_y);
    this->calGradient();
}

/**
 * @Author Chaoqun
 * @brief  有参构造函数
 * @param  参数
 * @date   2017/04/08
 */
Edge::Edge(const Point &p_a, const Point &p_b)
{
    this->p_start.copy(p_a);
    this->P_end.copy(p_b);
    this->calGradient();
}

/**
 * @Author Chaoqun
 * @brief  拷贝构造函数
 * @param  参数
 * @date   2017/04/08
 */
Edge::Edge(const Edge &edge)
{
    this->p_start.copy(edge.p_start);
    this->P_end.copy(edge.P_end);
    this->calGradient();
}

Edge::~Edge()
{

}

/**
 * @Author Chaoqun
 * @brief  获得一个端点
 * @date   2017/04/08
 */
Point *Edge::getStart()
{
    return &p_start;
}

/**
 * @Author Chaoqun
 * @brief  获得终点
 * @date   2017/04/08
 */
Point *Edge::getEnd()
{
    return &P_end;
}

/**
 * @Author Chaoqun
 * @brief  设置edge
 * @param  double a_x ,double a_y, double b_x, double b_y
 * @return 返回值
 * @date   2017/xx/xx
 */
void Edge::set(double a_x, double a_y, double b_x, double b_y)
{
    this->setStart(a_x, a_y);
    this->setEnd(b_x, b_y);
    this->calGradient();
}

/**
 * @Author Chaoqun
 * @brief  设置起点
 * @param  double a_x
 * @param  double a_y
 * @return void
 * @date   2017/04/08
 */
void Edge::setStart(double a_x, double a_y)
{
    this->p_start.set(a_x, a_y);
    this->calGradient();
}

/**
 * @Author Chaoqun
 * @brief  设置终点坐标
 * @param  double b_x
 * @param  double b_y
 * @return void
 * @date   2017/04/08
 */
void Edge::setEnd(double b_x, double b_y)
{
    this->P_end.set(b_x, b_y);
    this->calGradient();
}

/**
 * @Author Chaoqun
 * @brief  输出边的信息
 * @return void
 * @date   2017/04/08
 */
void Edge::print()
{
    this->p_start.print();
    std::cout <<"->";
    this->P_end.print();
}

/**
 * @Author Chaoqun
 * @brief  计算斜率
 * @return 斜率
 * @date   2017/04/08
 */
double Edge::calGradient()
{
    if(this->p_start.getY() == this->P_end.getY())
    {
        // 水平线不要计算斜率
        return 0;
    }
    this->neg_gradient = (this->P_end.getX() - this->p_start.getX()) /
            (this->P_end.getY() - this->p_start.getY());
    return this->neg_gradient;
}

/**
 * @Author Chaoqun
 * @brief  评价是否是水平线
 * @return bool true: Horizontal; false: not Horizontal
 * @date   2017/04/08
 */
bool Edge::is_Horizontal()
{
    if(this->p_start.getY() == this->P_end.getY())
    {
        return true;
    }
    else
        return false;
}
