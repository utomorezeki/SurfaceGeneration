#ifndef CATMULLCLARK_H
#define CATMULLCLARK_H

#include "mesh.h"
#include "catmulloriginal.h"

class CatmullClark
{
public:
    CatmullClark(){vertexOri = CatmullOriginal(); edgeOri = CatmullOriginal(); faceOri = CatmullOriginal();}
    void findVertexVert(Mesh* meshIn);
    void findEdgeVert(Mesh* meshIn);
    void findFaceVert(Mesh* meshIn);
    void generateFaces(Mesh* meshIn);
    Mesh generateMesh(Mesh* meshIn);

private:
    Mesh subdivMesh;
    CatmullOriginal vertexOri;
    CatmullOriginal edgeOri;
    CatmullOriginal faceOri;
};

#endif // CATMULLCLARK_H
