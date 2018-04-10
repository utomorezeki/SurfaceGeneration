#ifndef CATMULLORIGINAL_H
#define CATMULLORIGINAL_H

#include "mesh.h"
#include <QVector>

class CatmullOriginal {
public:
    CatmullOriginal(){}
    void addVertex(int originalV, GeomVert newVert);
    GeomVert getNewVertex(int originalV);
    void clear();

private:
    vector<GeomVert> list;
    QVector<int> listNum;
};

#endif // CATMULLORIGINAL_H
