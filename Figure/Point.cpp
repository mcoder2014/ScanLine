#include "Point.h"
#include <iostream>
using namespace Mcoder;         // 自定义的类型都放在这个命名空间里了

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(double x, double y)
{
    this->x = (int)x;
    this->y = (int)y;
}

// 拷贝构造函数
Point::Point(const Point &point)
{
    this->x = point.x;
    this->y = point.y;
}

void Point::setX(double x)
{
    this->x = x;
}

double Point::getX()
{
    return this->x;
}

void Point::setY(double y)
{
    this->y = y;
}

double Point::getY()
{
    return this->y;
}

/**
 * @Author Chaoqun
 * @brief  设置点
 * @param  double x
 * @param  double y
 * @date   2017/04/08
 */
void Point::set(double x, double y)
{
    this->x = x;
    this->y = y;
}

// 复制另一个点
void Point::copy(const Point &point)
{
    this->x = point.x;
    this->y = point.y;
}

/**
 * @Author Chaoqun
 * @brief  输出点的信息
 * @return void
 * @date   2017/04/08
 */
void Point::print()
{
    std::cout<< "<" << this->x
             << "," << this->y <<">";
}

// 重载运算符等于号
Point &Point::operator =(const Point &point)
{
    this->x = point.x;
    this->y = point.y;

    return *this;
}
