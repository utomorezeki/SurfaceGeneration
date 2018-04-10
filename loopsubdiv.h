#ifndef LOOPSUBDIV_H
#define LOOPSUBDIV_H

#include "mesh.h"
#include "catmulloriginal.h"

class LoopSubdiv
{
public:
    LoopSubdiv(){vertexOri = CatmullOriginal(); edgeOri = CatmullOriginal();}
    void calculateEdgeVert(Mesh *meshIn);
    void calculateVertVert(Mesh *meshIn);
    Mesh calculateMesh(Mesh *meshIn);

private:
    Mesh subdivMesh;
    CatmullOriginal edgeOri;
    CatmullOriginal vertexOri;
};

#endif // LOOPSUBDIV_H
