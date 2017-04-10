#include "customwidget.h"
#include <gl/glut.h>
#include <QMessageBox>
#include <QtDebug>

/**
 * 本类的坐标体系，以画面中心为 原点(0,0) ,因鼠标获取的坐标和openGL 坐标不相符
 * 设mouse坐标为(x, y); 屏幕宽为w, 屏幕高为h;
 * 则转换 (w/2 + x, h/2 - y)
 */

/**
 * @Author Chaoqun
 * @brief  构造函数
 * @param  QWidget *parent
 * @date   2017/04/05
 */
CustomWidget::CustomWidget(QWidget *parent)
    : QGLWidget(parent)
{
    this->modeFlag = 0;     // 初始默认是无操作状态
    this->temp = NULL;
    this->pushButton = -1;
    this->setMouseTracking(true);       // 发起鼠标监控
    this->scale = 1.0;      // widget缩放倍数默认为 1
    this->currentColor.setRgb(0,0,0);   // 初始颜色为黑色
}

CustomWidget::~CustomWidget()
{
    // 多边形
    if(this->temp !=NULL)
    {
        delete this->temp;
        this->temp = NULL;
    }
}

/**
 * @Author Chaoqun
 * @brief  删除上一个多边形
 * @date   2017/04/07
 */
void CustomWidget::backPolygon()
{
    if(this->modeFlag == 2)
    {
        // 如果正在画多边形，尚未画完，删除正在画的多边形
        delete this->temp;
        this->temp = NULL;
        this->modeFlag = 1;     // 置为未绘制状态，防止空指针错误
    }
    else if(this->polygons.size() > 0)
    {
        this->polygons.pop_back();
    }
    this->updateGL();       // 删除后随即刷新场景
}

/**
 * @Author Chaoqun
 * @brief  清空所有多边形
 * @date   2017/04/07
 */
void CustomWidget::cleanPolygons()
{
    if(this->modeFlag == 2)
    {
        // 如果正在画多边形，尚未画完，删除正在画的多边形
        delete this->temp;
        this->temp = NULL;
        this->modeFlag = 1;     // 置为未绘制状态，防止空指针错误
    }

    if(this->polygons.size() > 0)
    {
        this->polygons.clear();
    }

    this->updateGL();       // 删除后随机刷新
}

/**
 * @Author Chaoqun
 * @brief  获得画板缩放倍数
 * @date   2017/04/08
 */
float CustomWidget::getScale()
{
    return this->scale;
}

/**
 * @Author Chaoqun
 * @brief  初始化面板
 * @date   2017/04/06
 */
void CustomWidget::initializeGL()
{
    glShadeModel( GL_SMOOTH );              // 设置着色模式 参数可以是 GL_SMOOTH 光滑着色 或 GL_FLAT 恒定着色
    glClearColor( 1.0, 1.0, 1.0, 0.0 );     // 指定清空颜色的值
    glClearDepth( 1.0 );                    // 指定深度缓冲区的清除值
    glEnable( GL_DEPTH_TEST );              // 启用深度测试
    glDepthFunc( GL_LEQUAL );               // GL_LEQUAL,如果输入的深度值小于或等于参考值
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );    // 表示颜色和纹理坐标插补的质量。 应选择最正确或最高质量的选项

//    boundMouse();               // 绑定鼠标操作
}

/**
 * @Author Chaoqun
 * @brief  用来渲染当前场景
 * @param  参数
 * @date   2017/xx/xx
 */
void CustomWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );       // 清空颜色
    glLoadIdentity();

    glColor4f(0.5,0.5,0.5,1.0);

    for(int i = 0 ; i < this->polygons.size(); i++)
    {
        //qDebug() << "执行了polygon->paint()"<< i ;
        //(this->polygons[i])->paint();   // 绘制图形
        //(this->polygons[i])->scan();      // 扫描线填充
        (this->polygons[i])->scanLine();
        glColor4f(0.5,0.5,0.5,1.0);
        (this->polygons[i])->paint();   // 绘制图形
    }

    // 绘制正在画的多边形
    if(this->temp != NULL)
    {
        //qDebug() << "执行了temp-> paint()";
        this->temp->paint(1);
        glBegin(GL_LINES);
           Point * start = this->temp->getEndPoint();
           glVertex2f(start->getX(),start->getY());
           glVertex2f(this->mouse_x,this->mouse_y);
        glEnd();
    }

    //qDebug("执行了paintGL()");
}

/**
 * @Author Chaoqun
 * @brief  自动适应屏幕大小
 * @param  宽度
 * @date   2017/04/06
 */
void CustomWidget::resizeGL(int width, int height)
{

    this->resizeGL(width,height,this->scale);    // 用当前的缩放倍数
}

/**
 * @Author Chaoqun
 * @brief  调整画面缩放值
 * @param  int width 屏幕宽度
 * @param  int height 屏幕高度
 * @param  int scale  缩放倍数
 * @date   2017/04/08
 */
void CustomWidget::resizeGL(int width, int height, float scale)
{

    if ( height == 0 )      // 好像高是除数，不能为0
    {
      height = 1;
    }

    glViewport( 0, 0, (GLint)width, (GLint)height );    // 从 0,0 开始绘制指定大小的视图
    glMatrixMode( GL_PROJECTION );                      // GL_PROJECTION,对投影矩阵应用随后的矩阵操作.
    glLoadIdentity();                                   // 重置当前指定的矩阵为单位矩阵
    //gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );         // 设置锥台投影

    int part_width = (int)width * scale * 0.5;          // 实际屏幕中显示的范围 -x
    int part_height = (int)height * scale * 0.5;        // 实际屏幕中显示的范围 -y

    gluOrtho2D(-part_width,part_width,
               -part_height,part_height);                       // 设置渲染为2D
    glMatrixMode( GL_MODELVIEW );                       // GL_MODELVIEW,对模型视景矩阵堆栈应用随后的矩阵操作
    glLoadIdentity();

    this->width = width;        // 屏幕的宽
    this->height = height;      // 屏幕的高

    this->updateGL();       // 调整完大小要更新渲染
}

/**
 * @Author Chaoqun
 * @brief  单纯调整缩放倍数
 * @param  float scale
 * @date   2017/04/08
 */
void CustomWidget::resizeGL(float scale)
{
    this->resizeGL(this->width,this->height,scale);
    this->scale = scale;
}

/**
 * @Author Chaoqun
 * @brief  设置绘画颜色
 * @param  QColor color
 * @return void
 * @date   2017/04/10
 */
void CustomWidget::setColor(QColor color)
{
    this->currentColor.setRgba(color.rgba());       // 设置颜色
}

/**
 * @Author Chaoqun
 * @brief  获得所有多边形
 * @param  void
 * @return vector<Polygon *> *
 * @date   2017/xx/xx
 */
vector<Mcoder::Polygon *> *CustomWidget::getPolygons()
{
    return &(this->polygons);
}

/**
 * @Author Chaoqun
 * @brief  鼠标移动事件响应函数
 * @param  QMouseEvent *event
 * @date   2017/04/06
 */
void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    this->convertMouse(event);

    if(this->modeFlag != 0)
        this->updateGL();       // 更新渲染
    //qDebug()<<"鼠标移动";
}

/**
 * @Author Chaoqun
 * @brief  鼠标点击响应参数
 * @param  QMouseEvent *event
 * @date   2017/04/06
 */
void CustomWidget::mousePressEvent(QMouseEvent *event)
{
    this->convertMouse(event);

    if(this->modeFlag == 1 || this->modeFlag == 2)
    {
        // 绘制多边形
        // 点下右键，结束绘制
        if(event->button() == Qt::RightButton)
        {
        }
        else if(event->button() == Qt::LeftButton)
        {
        }
    }

    this->pushButton = event->button();      // 暂存点下的鼠标
    this->updateGL();       // 更新渲染
}

/**
 * @Author Chaoqun
 * @brief  鼠标释放响应函数
 * @param  QMouseEvent *event
 * @date   2017/04/06
 */
void CustomWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->convertMouse(event);

    qDebug() << "x: "<<this->mouse_x
             << " y: "<<this->mouse_y;

    if(this->pushButton == Qt::LeftButton)
    {
        // 如果是鼠标左键松开
        if(this->modeFlag == 1)
        {
            // 开始绘制第一个多边形
            this->temp = new Mcoder::Polygon();     // 新建多边形

            this->temp->push(this->mouse_x,this->mouse_y);

            this->modeFlag = 2;           // 绘制完第一个就进入状态2
        }
        else if(this->modeFlag == 2)
        {
            // 绘制下一个点

            this->temp->push(this->mouse_x,this->mouse_y);
        }
    }
    else if(this->pushButton == Qt::RightButton)
    {
        // 如果是鼠标右键松开
        if(this->modeFlag ==1)
        {
            // 当作误触进行处理
        }
        else if(this->modeFlag == 2)
        {
            // 结束绘制
            //this->temp->push(this->mouse_x,this->height - this->mouse_y);
            if(this->temp->getSize() > 2)
            {
                this->temp->setColor(this->currentColor);   // 设置多边形填充颜色
                this->polygons.push_back(this->temp);       // 将多边形添加到数组
                this->temp = NULL;                          // 指针置空
                this->modeFlag = 1;
            }
            else
            {
                // 提醒用户，需要绘制多少个点才可以
                QMessageBox::StandardButton reply;
                reply = QMessageBox::information(this,
                                tr("Warning! Your manipulation is against the rule!"),
                                tr("You should draw at least three points."),
                                                     QMessageBox::Ok);
            }
        }
    }

    this->pushButton = -1;
    this->updateGL();       // 更新渲染
}

/**
 * @Author Chaoqun
 * @brief  用来更改鼠标坐标与实际需求的不对应的地方,结果保存在 this->mouse_x, this->mouse_y 中
 * @param  QMouseEvent *event 鼠标事件
 * @date   2017/04/07
 */
void CustomWidget::convertMouse(QMouseEvent *event)
{
    this->mouse_x = scale * (event->x()-this->width/2);
    this->mouse_y = scale * (this->height/2.0 - event->y());
}




