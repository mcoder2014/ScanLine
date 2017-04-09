#include "iopolygon.h"
#include <QDebug>
#include <QJsonArray>
#include <array>
#include <vector>
#include <iterator>

using std::array;

IOpolygon::IOpolygon()
{

}

IOpolygon::IOpolygon(const QFile &file)
{
    this->file.setFileName(file.fileName());    // 复制别人的QFile
}

/**
 * @Author Chaoqun
 * @brief  用字符串初始化 QFile
 * @param  const QString &str
 * @date   2017/04/09
 */
IOpolygon::IOpolygon(const QString &str)
    :file(str)
{
}

/**
 * @Author Chaoqun
 * @brief  设置写出文件路径
 * @param  const QString &fileName
 * @return void
 * @date   2017/04/09
 */
void IOpolygon::setFileName(const QString &fileName)
{
    this->file.setFileName(fileName);
}

/**
 * @Author Chaoqun
 * @brief  将画板中的多边形写出到文件
 * @param  vector<Polygon *>
 * @param  QFile * file
 * @return int 成功 1 失败 0
 * @date   2017/04/09
 */
int IOpolygon::writeFile(vector<Polygon *> *polygons, QFile *file)
{
    if(file != NULL)
    {
        this->file.setFileName(file->fileName());
    }

    return -1;
}

/**
 * @Author Chaoqun
 * @brief  写文件
 * @param  QFile * file
 * @return vector<Polygon *>
 * @date   2017/04/09
 */
vector<Polygon *> IOpolygon::readFile(QFile *file)
{
    return (vector<Polygon *>());
}

/**
 * @Author Chaoqun
 * @brief  将多边形转化为QJsonObject
 * @param  Polygon * polygon
 * @return QJsonObject
 * @date   2017/04/09
 */
QJsonObject* IOpolygon::convert(Polygon* polygon)
{
    QJsonObject * json_obj;
    QJsonArray* json_array = new QJsonArray();
    vector<Point *>* points = polygon->getPoints();     // 获得点

    for(int i = 0; i < points->size() ; i++)
    {
                Point* point = points->at(i);
                json_obj = new QJsonObject();
                json_obj->insert("x",point->getX());
                json_obj->insert("y",point->getY());

//                qDebug() << "x:" << point->getX()
//                         << ",y:" << point->getY();

                json_array->append(*json_obj);
    }

    json_obj = new QJsonObject();
    json_obj->insert("points",*json_array);

    return json_obj;
}

/**
 * @Author Chaoqun
 * @brief  从JSON 字符串转换到 Polygon
 * @param  QJsonObject &json_obj
 * @return Polygon *
 * @date   2017/04/09
 */
Polygon *IOpolygon::fromJson(QJsonObject &json_obj)
{
    if(json_obj["points"] == NULL)
    {
        qDebug() << "不是我们需要的类 ";
        return NULL;
    }

    QJsonValue value = json_obj.value("points");
    if(!value.isArray())
    {
        qDebug() << "不是点 " ;
        return NULL;
    }
    QJsonArray json_array = value.toArray();

    Polygon * polygon = new Polygon();          // 多边形

    for(int i = 0; i < json_array.size(); i++)
    {
        QJsonValueRef ref = json_array[i];
        QJsonObject obj = ref.toObject();
        polygon->push(obj["x"].toInt(), obj["y"].toInt());
        //qDebug() <<obj["x"].toInt() <<","<<obj["y"].toInt();
    }

    return polygon;
}
