#ifndef POINT_H
#define POINT_H

namespace Mcoder {
// 自定义点数据结构
class Point
{
public:
    Point();
    Point(double x, double y);
    Point(const Point& point);      // 拷贝构造函数

    void setX(double x);
    double getX();
    void setY(double y);
    double getY();

    void copy(const Point& point);

// 重载运算符

    Point &operator =(const Point& point);      // 重载等于号



private:
    double x;   // 点的X坐标
    double y;   // 点的Y坐标
};
}


#endif // POINT_H
