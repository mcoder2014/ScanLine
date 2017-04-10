#ifndef IOPOLYGON_H
#define IOPOLYGON_H

#include <QFile>
#include <QJsonObject>
#include <vector>
#include "Figure/Polygon.h"
using namespace Mcoder;

// 用来读取或写出画布文件
class IOpolygon
{
public:
    IOpolygon();
    IOpolygon(const QFile &file );
    IOpolygon(const QString& str);

    void setFileName(const QString& fileName);      // 设置文件路径

    int writeFile(vector<Mcoder::Polygon *>* polygons, QFile *file = 0);  // 写出文件到xxx
    vector<Mcoder::Polygon *> readFile(QFile *file = 0);    // 读文件
    QJsonObject *convert(Mcoder::Polygon *polygon);           // 将一个Polygon转换成QJsonObject
    Mcoder::Polygon *fromJson(QJsonObject &json_obj );

    QJsonObject *convert(vector<Mcoder::Polygon *> *polygons);     // 将vector向量转换为QJsonObject
    vector<Mcoder::Polygon *> * toPolygons(QJsonObject &json_obj);   // 将一个QJsonObject转换为 Polygons


private:
    QFile file;

};

#endif // IOPOLYGON_H
