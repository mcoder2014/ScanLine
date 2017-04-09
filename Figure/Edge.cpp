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
}

/**
 * @Author Chaoqun
 * @brief  构造函数
 * @param  int a_x
 * @param  int a_y
 * @param  int b_x
 * @param  int b_y
 * @date   2017/04/08
 */
Edge::Edge(int a_x, int a_y, int b_x, int b_y)
{
    this->p_start.set(a_x, a_y);
    this->P_end.set(b_x, b_y);
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
 * @param  int a_x ,int a_y, int b_x, int b_y
 * @return 返回值
 * @date   2017/xx/xx
 */
void Edge::set(int a_x, int a_y, int b_x, int b_y)
{
    this->setStart(a_x, a_y);
    this->setEnd(b_x, b_y);
}

/**
 * @Author Chaoqun
 * @brief  设置起点
 * @param  int a_x
 * @param  int a_y
 * @return void
 * @date   2017/04/08
 */
void Edge::setStart(int a_x, int a_y)
{
    this->p_start.set(a_x, a_y);
}

/**
 * @Author Chaoqun
 * @brief  设置终点坐标
 * @param  int b_x
 * @param  int b_y
 * @return void
 * @date   2017/04/08
 */
void Edge::setEnd(int b_x, int b_y)
{
    this->P_end.set(b_x, b_y);
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
