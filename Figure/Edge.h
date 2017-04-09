#ifndef EDGE_H
#define EDGE_H
#include "Point.h"

namespace Mcoder {
// 自定义边数据结构
class Edge
{
public:
    Edge();
    Edge(int a_x, int a_y, int b_x, int b_y);
    Edge(const Point &p_a, const Point &p_b);
    Edge(const Edge &edge);
    ~Edge();

    Point* getStart();      // 获得一个端点
    Point* getEnd();        // 获得另一个端点

    void set(int a_x, int a_y, int b_x, int b_y);
    void setStart(int a_x,int a_y);
    void setEnd(int b_x, int b_y);

    void print();

private:
    // 这两个点的顺序与画多边形时的顺序一个该是相同的
    Point p_start;
    Point P_end;
};

}


#endif // EDGE_H
