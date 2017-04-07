#include "customwidget.h"
#include <gl/glut.h>
#include <QtDebug>


CustomWidget::CustomWidget(QWidget *parent)
    : QGLWidget(parent)
{
    this->modeFlag = 1;     // 初始默认是无操作状态
    this->temp = NULL;
    this->pushButton = -1;
    this->setMouseTracking(true);       // 发起鼠标监控
}

CustomWidget::~CustomWidget()
{
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
        qDebug() << "执行了polygon->paint()"<< i ;
        (this->polygons[i])->paint();   // 绘制图形
    }

    // 绘制正在画的多边形
    if(this->temp != NULL)
    {
        qDebug() << "执行了temp-> paint()";
        this->temp->paint(1);
    }


//    glBegin( GL_TRIANGLES );                    // 画三角形
//      glVertex2f(  1.0, 1.0 );
//      glVertex2f( 500.0, 100.0);
//      glVertex2f(  100.0, 500.0);
//    glEnd();

//    glBegin( GL_QUADS );
//      glVertex2f( 1000.0,  1000.0);
//      glVertex2f( 300.0 , 300.0);
//      glVertex2f(  500.0, 600.0);
//      glVertex2f( 900.0, 1.0);
//    glEnd();

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
    if ( height == 0 )      // 好像高是除数，不能为0
    {
      height = 1;
    }

    glViewport( 0, 0, (GLint)width, (GLint)height );    // 从 0,0 开始绘制指定大小的视图
    glMatrixMode( GL_PROJECTION );                      // GL_PROJECTION,对投影矩阵应用随后的矩阵操作.
    glLoadIdentity();                                   // 重置当前指定的矩阵为单位矩阵
    //gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );         // 设置锥台投影
    gluOrtho2D(0,width,0,height);                       // 设置渲染为2D
    glMatrixMode( GL_MODELVIEW );                       // GL_MODELVIEW,对模型视景矩阵堆栈应用随后的矩阵操作
    glLoadIdentity();

    this->width = width;
    this->height = height;

}

/**
 * @Author Chaoqun
 * @brief  鼠标移动事件响应函数
 * @param  QMouseEvent *event
 * @date   2017/04/06
 */
void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    this->mouse_x = event->x();
    this->mouse_y = event->y();

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
    this->mouse_x = event->x();
    this->mouse_y = event->y();
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
    this->mouse_x = event->x();
    this->mouse_y = event->y();

    qDebug() << "x: "<<this->mouse_x
             << " y: "<<this->mouse_y;

    if(this->pushButton == Qt::LeftButton)
    {
        // 如果是鼠标左键松开
        if(this->modeFlag == 1)
        {
            // 开始绘制第一个多边形
            this->temp = new Mcoder::Polygon();     // 新建多边形

            this->temp->push(this->mouse_x,this->height - this->mouse_y);

            this->modeFlag = 2;           // 绘制完第一个就进入状态2
        }
        else if(this->modeFlag == 2)
        {
            // 绘制下一个点

            this->temp->push(this->mouse_x,this->height - this->mouse_y);
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
            // 绘制下一个点
            this->temp->push(this->mouse_x,this->height - this->mouse_y);

            this->polygons.push_back(this->temp);   // 将多边形添加到数组
            this->temp = NULL;          // 指针置空
            this->modeFlag = 1;
        }
    }

    this->pushButton = -1;
    this->updateGL();       // 更新渲染
}




