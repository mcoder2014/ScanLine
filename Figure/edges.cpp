#include "edges.h"

EdgeS::EdgeS()
{

}

/**
 * @Author Chaoqun
 * @brief  构造函数
 * @param  double xi, double dx, int ymax
 * @date   2017/04/08
 */
EdgeS::EdgeS(double xi, double dx, int ymax)
{
    this->xi = xi;
    this->dx = dx;
    this->ymax = ymax;
}
