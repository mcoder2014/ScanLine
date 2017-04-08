#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <list>
#include "Point.h"
#include "Edge.h"
#include "edges.h"
using std::vector;
using std::list;


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

    void scanLine();            // 扫描线填充算法

    bool rebuildEdge();      // 生成边
    bool buildEdgeTable();   // 生成sorted edge table
    void print();            // 输出多边形信息

private:
    vector<Point*> points;       // 点
    vector<Edge*> edges;         // 边
    vector<List<EdgeS*>*> sortedEdgeTable;

    Point min;          // 多边形包围矩形的 左下角
    Point max;          // 多边形包围矩形的 右下角
};

}

#endif // POLYGON_H
