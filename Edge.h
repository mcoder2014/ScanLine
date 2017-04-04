#ifndef EDGE_H
#define EDGE_H
#include "Point.h"

namespace Mcoder {
// 自定义边数据结构
class Edge
{
public:
    Edge();
private:
    Point* p_start;
    Point* P_end;
};



}


#endif // EDGE_H
