#ifndef MOUSE_H
#define MOUSE_H
/**
 * @Author Chaoqun
 * @brief  鼠标点击的响应函数
 * @param  int button 哪个键被点下
 * @param  int state  状态
 * @param  int x    x 坐标
 * @param  int y    y 坐标
 * @date   2017/xx/xx
 */
void myMouse(int button, int state, int x, int y)
{
       qDebug("\n鼠标被点下：button: ", button,
              " state: ", state,
              " x: ", x, " y: ",y , "\n");
}

/**
 * @Author Chaoqun
 * @brief  鼠标移动响应函数
 * @param  int x x值
 * @param  int y y值
 * @date   2017/xx/xx
 */
void myPassiveMotion(int x, int y)
{
    qDebug("*");
}

#endif // MOUSE_H
