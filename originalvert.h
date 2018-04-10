#ifndef ORIGINALVERT_H
#define ORIGINALVERT_H

#include "mesh.h"
#include <QVector>

class OriginalVert {
public:
    OriginalVert(){}
    void addVertex(int originalV, GeomVert newVert);
    vector<GeomVert> getVertexList(int originalV);

private:
    QVector<vector<GeomVert>> list;
    QVector<int> listNum;
};

#endif // ORIGINALVERT_H
