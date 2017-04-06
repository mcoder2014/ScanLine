#include "customwidget.h"
#include <gl/glut.h>
#include "mouse.h"

CustomWidget::CustomWidget(QWidget *parent)
    : QGLWidget(parent)
{
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
 * @brief  画图
 * @param  参数
 * @date   2017/xx/xx
 */
void CustomWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );       // 清空颜色
    glLoadIdentity();

    glColor4f(0.3,0.3,0.3,1.0);

    glBegin( GL_TRIANGLES );                    // 画三角形
      glVertex2f(  1.0, 1.0 );
      glVertex2f( 500.0, 100.0);
      glVertex2f(  100.0, 500.0);
    glEnd();

    //glTranslatef(  3.0,  0.0);

    glBegin( GL_QUADS );
      glVertex2f( 1000.0,  1000.0);
      glVertex2f( 300.0 , 300.0);
      glVertex2f(  500.0, 600.0);
      glVertex2f( 900.0, 1.0);
    glEnd();
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

}

/**
 * @Author Chaoqun
 * @brief  用来绑定鼠标操作
 * @date   2017/04/06
 */
void CustomWidget::boundMouse()
{
//    glutMouseFunc(&myMouse);               // 鼠标点击消息监控，即监控鼠标是否被点击，若被点击就调用myMouse函数
//    glutPassiveMotionFunc(&myPassiveMotion);     // 鼠标移动消息监控，即监控鼠标是否移动，若移动就调用myPassiveMotion函数
}



