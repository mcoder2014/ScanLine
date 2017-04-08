#ifndef EDGE_H
#define EDGE_H
#include "Point.h"

namespace Mcoder {
// 自定义边数据结构
class Edge
{
public:
    Edge();
    Edge(double a_x, double a_y, double b_x, double b_y);
    Edge(const Point &p_a, const Point &p_b);
    Edge(const Edge &edge);
    ~Edge();

    Point* getStart();      // 获得一个端点
    Point* getEnd();        // 获得另一个端点

    void set(double a_x, double a_y, double b_x, double b_y);
    void setStart(double a_x,double a_y);
    void setEnd(double b_x, double b_y);

    void print();
    double calGradient();       // 计算斜率
    bool is_Horizontal();       // 评价是否是水平线

private:
    // 这两个点的顺序与画多边形时的顺序一个该是相同的
    Point p_start;
    Point P_end;
    double neg_gradient;        // 斜率的倒数
};

}


#endif // EDGE_H
