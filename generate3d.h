#ifndef GENERATE3D_H
#define GENERATE3D_H

#include <QVector>
#include "mesh.h"

class Gen3D
{
public:

    static void revCalcFaces(QVector<double> gr_x, QVector<double> gr_y, Mesh *mesh, int revSlices);
    static vector<GeomVert> revCalcCir(int revSlices, double xVal, double yVal);
    static void extCalcFaces(QVector<double> gr_x, QVector<double> gr_y, Mesh *mesh, int extDepth);
    static vector<GeomVert> extCalcPlane(double yVal, double xVal, int extDepth);
    static void sweepCalcFaces(QVector<double> gr_x, QVector<double> gr_y, QVector<double> gr2_x, QVector<double> gr2_y, Mesh *mesh);
    static vector<GeomVert> sweepCalcPlane(double yVal, double xVal, QVector<double> gr2_z, QVector<double> gr2_y);
private:
    Gen3D(){}
};


#endif // GENERATE3D_H
