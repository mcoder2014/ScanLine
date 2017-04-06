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
    Polygon(vector<Point *> &points);

    void push(int x, int y);
    vector<Point *> * getPoints();
    void setPoints(vector<Point *>& points);

    int getSize();               // 该多边形有多少个点
    Point* getPoint(int i);      // 获得指定的点
    Point *getEndPoint();

    void paint(int line_strip = 0);             // 用来画多边形

private:
    vector<Point*> points;       // 点
    //vector<Edge*> edges;         // 边
};

}

#endif // POLYGON_H
