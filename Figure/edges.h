#ifndef EDGES_H
#define EDGES_H


class EdgeS
{
public:
    EdgeS();
    EdgeS(double xi, double dx, int ymax);
    int ymax;
    double xi,dx;
};

#endif // EDGES_H
