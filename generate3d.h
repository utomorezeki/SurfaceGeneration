#ifndef GENERATE3D_H
#define GENERATE3D_H

#include <QVector>
#include "mesh.h"

class Gen3D
{
public:

    static void revCalcFaces(QVector<double> gr_x, QVector<double> gr_y, Mesh *mesh);
    static vector<GeomVert> revCalcCir(double interval, double xVal);
    static void extCalcFaces(QVector<double> gr_x, QVector<double> gr_y, Mesh *mesh);
    static vector<GeomVert> extCalcPlane(double yVal, double xVal);
private:
    Gen3D(){}
};


#endif // GENERATE3D_H
