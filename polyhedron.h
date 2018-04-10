#define POLYHEDRON_H

#include <QVector>
#include "mesh.h"

class Polyhedron {
public:
    Polyhedron(int rowIn, int columnIn) { row = rowIn; column = columnIn; }

    GeomVert getData(int rowD, int colD);
    void insertData(GeomVert dataIn);
    void insertData(vector<GeomVert> dataIn);
    int getCol(){return column;}
    int getRow(){return row;}

private:
    int row, column;
    vector<GeomVert> data;
};
