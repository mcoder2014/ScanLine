#ifndef POLYGON_H
#define POLYGON_H
#include<vector>
#include"Point.h"
#include"Edge.h"
using std::vector;


namespace Mcoder {
class Polygon
{
public:
    Polygon();

private:
    vector<Point*> points;       // 点
    vector<Edge*> edges;         // 边
};

}

#endif // POLYGON_H
