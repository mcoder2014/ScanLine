#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <list>
#include <QColor>
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
    bool buildEdgeTable();   // 生成sorted edge table
    void scan();        // 扫描
    void print();            // 输出多边形信息

    void setColor(QColor color);       // 将QColor转换为rgb
    double getRed(){return this->red;}
    void setRed(double red){this->red = red;}
    double getGreen(){return this->green;}
    void setGreen(double green){this->green = green;}
    double getBlue(){return this->blue;}
    void setBlue(double blur){this->blue = blue;}

private:
    vector<Point*> points;       // 点
    vector<vector<EdgeS*>*> sortedEdgeTable;
    vector<Edge* > edge_horizontal;     // 水平边

    Point min;          // 多边形包围矩形的 左下角
    Point max;          // 多边形包围矩形的 右下角

    double red, green, blue;        // 绘图的颜色

    void addEdgeToTable(Point *p_start, Point *p_end);             // 添加边到排序边表
    void printScanLine(vector<EdgeS*> activeEdgeTable, int y);     // 画活动边表的扫描线
    void printHorizontalLine(vector<Edge*> edgeHorizontal);        // 画水平线

};

}

#endif // POLYGON_H
