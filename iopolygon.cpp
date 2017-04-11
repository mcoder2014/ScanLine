#include "iopolygon.h"
#include <QDebug>
#include <QJsonArray>
#include <array>
#include <vector>
#include <iterator>
#include <QJsonDocument>

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

    // 文件不存在要创建文件
    if(!this->file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "文件打开失败";
        return 1;
    }
    QTextStream txtOutput(&(this->file));   // 新建文件输出流

    QJsonObject * json_obj = this->convert(polygons);       // 转换成QJsonOnject
    QJsonDocument * json_doc = new QJsonDocument(*json_obj);    // 准备导出json文本
    QByteArray json_bytearray = json_doc->toJson(QJsonDocument::Indented);
    //QString json_str(json_bytearray);

    txtOutput << json_bytearray << endl;

    this->file.close();     // 使用后要关闭文件

    return 1;
}

/**
 * @Author Chaoqun
 * @brief  写文件
 * @param  QFile * file
 * @return vector<Polygon *>
 * @date   2017/04/09
 */
vector<Polygon *>* IOpolygon::readFile(QFile *file)
{
    if(file != NULL)
    {
        this->file.setFileName(file->fileName());
        return NULL;
    }
    if(!this->file.exists())
    {
        qDebug() << "文件不存在 ";
        return NULL;
    }
    // 文件不存在要报错
    if(!this->file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "文件打开失败 ";
        return NULL;
    }

    QTextStream txtInput(&(this->file));        // 设置文件流
    QString str = txtInput.readAll();           // 读取全部字符串
    QJsonDocument jd_doc = QJsonDocument::fromJson(str.toLocal8Bit(),Q_NULLPTR);
    QJsonObject js_obj = jd_doc.object();       // get obj
    vector<Polygon *>* vec = this->toPolygons(js_obj);

    return vec;
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
    json_obj->insert("red",polygon->getRed());
    json_obj->insert("green",polygon->getGreen());
    json_obj->insert("blue",polygon->getBlue());

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
    if(json_obj.value("points").isNull())
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

    // 获得颜色
    double red = json_obj.value("red").toDouble();
    polygon->setRed(red);
    double green = json_obj.value("green").toDouble();
    polygon->setGreen(green);
    double blue = json_obj.value("blue").toDouble();
    polygon->setBlue(blue);

    return polygon;
}

/**
 * @Author Chaoqun
 * @brief  将polygons数组转换为QJsonObject
 * @param  vector<Polygon *> *polygons
 * @return QJsonObject
 * @date   2017/04/10
 */
QJsonObject *IOpolygon::convert(vector<Polygon *> *polygons)
{
    int size = polygons->size();        // 获取多边形数量
    QJsonArray arr;                 // 新建一个空的QJsonArray

    for(int i = 0; i < size ; i++)
    {
        Polygon * temp = polygons->at(i);
        QJsonObject * json_obj = this->convert(temp);    // 转换对象
        qDebug() << i <<" of "<< size;
        arr.append( *json_obj );    // 加入到数组中
    }

    QJsonObject * json_obj = new QJsonObject();
    json_obj->insert("polygons",arr);               // 将多边形插入到对象中

    return json_obj;
}

/**
 * @Author Chaoqun
 * @brief  将QJsonObject转换为polygons
 * @param  QJsonObject &json_obj
 * @return vector<Polygon *> *
 * @date   2017/04/10
 */
vector<Polygon *> * IOpolygon::toPolygons(QJsonObject &json_obj)
{
    // 先判断是否包含 polygons
    if(json_obj["polygons"].isNull())
    {
        qDebug() << "不包含 polygon 字段 ";
        return new vector<Polygon *>();
    }

    QJsonValue polygons = json_obj.value("polygons");
    if(!polygons.isArray())
    {
        qDebug() << "polygons 不是数组";
    }
    QJsonArray json_array = polygons.toArray();
    vector<Polygon *> *poly_vec = new vector<Polygon *>();                 // 新建vector<Polygon *>

    int size = json_array.size();
    for(int i = 0; i < size; i++)
    {
        QJsonValue json_value =  json_array.at(i);
        QJsonObject temp_obj = json_value.toObject();
        Polygon* temp = this->fromJson(temp_obj);
        poly_vec->push_back(temp);
    }

    return poly_vec;        // 返回多边形
}
