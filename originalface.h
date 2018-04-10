#ifndef ORIGINALFACE_H
#define ORIGINALFACE_H

#include "mesh.h"
#include <QVector>

class OriginalFace {
public:
    OriginalFace(){}
    void addVertex(int originalF, GeomVert newVert);
    bool checkVertex(int originalF, GeomVert check);
    bool checkCommon(int faceNum, TopoVert currVert, vector<int> prevFidxes);
    GeomVert checkMember(vector<GeomVert> faceV, vector<GeomVert> vertV);
    vector<GeomVert> getVList(int originalF);

private:
    QVector<vector<GeomVert>> faceVertexlist;
    QVector<int> faceList;
};

#endif // ORIGINALFACE_H
