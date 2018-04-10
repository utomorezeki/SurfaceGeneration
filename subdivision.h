#ifndef SUBDIVISION_H
#define SUBDIVISION_H

#include "mesh.h"
#include "originalvert.h"
#include "originalface.h"

class Subdivision
{
public:
    static void dooSabinCalcFace(Mesh* meshIn, Mesh* meshOut, OriginalVert *oriVert, OriginalFace *oriFace);
    static void dooSabinCalcEdge(Mesh* meshIn, Mesh* meshOut, OriginalVert *oriVert);
    static void dooSabinCalcVert(Mesh* meshIn, Mesh* meshOut, OriginalVert *oriVert, OriginalFace *oriFace);
private:
    Subdivision(){}
    static GeomVert getCentroid(TopoFacet currface, Mesh* meshIn);
};

#endif // SUBDIVISION_H
