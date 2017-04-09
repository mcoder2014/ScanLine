#ifndef POINT_H
#define POINT_H

namespace Mcoder {
// 自定义点数据结构
class Point
{
public:
    Point();
    Point(int x, int y);
    Point(const Point& point);      // 拷贝构造函数

    void setX(int x);
    int getX();
    void setY(int y);
    int getY();

    void set(int x, int y);

    void copy(const Point& point);
    void print();       // 输出点的信息

// 重载运算符

    Point &operator =(const Point& point);      // 重载等于号



private:
    int x;   // 点的X坐标
    int y;   // 点的Y坐标
};
}


#endif // POINT_H
