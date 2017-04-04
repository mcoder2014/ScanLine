#include "customwidget.h"
#include <gl/glut.h>

CustomWidget::CustomWidget(QWidget *parent)
    : QGLWidget(parent)
{

}

CustomWidget::~CustomWidget()
{
}

// 设置初始化内容
void CustomWidget::initializeGL()
{
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void CustomWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();

    glTranslatef( -1.5,  0.0, -6.0 );

    glBegin( GL_TRIANGLES );
      glVertex3f(  0.0,  1.0,  0.0 );
      glVertex3f( -1.0, -1.0,  0.0 );
      glVertex3f(  1.0, -1.0,  0.0 );
    glEnd();

    glTranslatef(  3.0,  0.0,  0.0 );

    glBegin( GL_QUADS );
      glVertex3f( -1.0,  1.0,  0.0 );
      glVertex3f(  1.0,  1.0,  0.0 );
      glVertex3f(  1.0, -1.0,  0.0 );
      glVertex3f( -1.0, -1.0,  0.0 );
    glEnd();
}

// 重新设置窗口大小
void CustomWidget::resizeGL(int width, int height)
{
    if ( height == 0 )
    {
      height = 1;
    }
    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

}



