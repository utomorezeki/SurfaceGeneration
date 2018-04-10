#include "test.h"

void Test::test1DSB(Mesh *meshIn, Mesh *meshOut){
    vector<GeomVert> toBeAdd;
    GeomVert v1 = GeomVert(0.0, 0.0, 0.0);
    GeomVert v2 = GeomVert(10.0, 0.0, 0.0);
    GeomVert v3 = GeomVert(10.0, 10.0, 0.0);
    GeomVert v4 = GeomVert(0.0, 10.0, 0.0);

    toBeAdd.push_back(v1);
    toBeAdd.push_back(v2);
    toBeAdd.push_back(v3);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();
    toBeAdd.push_back(v1);
    toBeAdd.push_back(v3);
    toBeAdd.push_back(v4);
    meshIn->AddFacet(toBeAdd);

    OriginalVert oriVert;
    OriginalFace oriFace;
    Subdivision::dooSabinCalcFace(meshIn,meshOut, &oriVert, &oriFace);
    Subdivision::dooSabinCalcEdge(meshIn,meshOut, &oriVert);
    Subdivision::dooSabinCalcVert(meshIn,meshOut, &oriVert, &oriFace);
}

Mesh Test::test1CCL(Mesh *meshIn){
    vector<GeomVert> toBeAdd;
    GeomVert v1 = GeomVert(0.0, 0.0, 0.0);
    GeomVert v2 = GeomVert(10.0, 0.0, 0.0);
    GeomVert v3 = GeomVert(10.0, 10.0, 0.0);
    GeomVert v4 = GeomVert(0.0, 10.0, 0.0);

    toBeAdd.push_back(v1);
    toBeAdd.push_back(v2);
    toBeAdd.push_back(v3);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();
    toBeAdd.push_back(v1);
    toBeAdd.push_back(v3);
    toBeAdd.push_back(v4);
    meshIn->AddFacet(toBeAdd);

    CatmullClark catM = CatmullClark();
    return catM.generateMesh(meshIn);
}

Mesh Test::test1LOOP(Mesh *meshIn){
    vector<GeomVert> toBeAdd;
    GeomVert v1 = GeomVert(0.0, 0.0, 0.0);
    GeomVert v2 = GeomVert(10.0, 0.0, 0.0);
    GeomVert v3 = GeomVert(10.0, 10.0, 0.0);
    GeomVert v4 = GeomVert(0.0, 10.0, 0.0);

    toBeAdd.push_back(v1);
    toBeAdd.push_back(v2);
    toBeAdd.push_back(v3);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();
    toBeAdd.push_back(v1);
    toBeAdd.push_back(v3);
    toBeAdd.push_back(v4);
    meshIn->AddFacet(toBeAdd);

    LoopSubdiv loopS = LoopSubdiv();
    return loopS.calculateMesh(meshIn);
}

void Test::test2DSB(Mesh *meshIn, Mesh *meshOut){
    vector<GeomVert> toBeAdd;
    GeomVert v1 = GeomVert(0.0, 0.0, 0.0);
    GeomVert v2 = GeomVert(10.0, 0.0, 0.0);
    GeomVert v3 = GeomVert(10.0, 10.0, 0.0);
    GeomVert v4 = GeomVert(0.0, 10.0, 0.0);

    toBeAdd.push_back(v1);
    toBeAdd.push_back(v2);
    toBeAdd.push_back(v3);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();
    toBeAdd.push_back(v1);
    toBeAdd.push_back(v3);
    toBeAdd.push_back(v4);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();

    v1 = GeomVert(0.0, 10.0, 0.0);
    v2 = GeomVert(10.0, 10.0, 0.0);
    v3 = GeomVert(10.0, 20.0, 0.0);
    v4 = GeomVert(0.0, 20.0, 0.0);

    toBeAdd.push_back(v1);
    toBeAdd.push_back(v2);
    toBeAdd.push_back(v3);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();
    toBeAdd.push_back(v1);
    toBeAdd.push_back(v3);
    toBeAdd.push_back(v4);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();

    v1 = GeomVert(10.0, 10.0, 0.0);
    v2 = GeomVert(20.0, 10.0, 0.0);
    v3 = GeomVert(20.0, 20.0, 0.0);
    v4 = GeomVert(10.0, 20.0, 0.0);

    toBeAdd.push_back(v1);
    toBeAdd.push_back(v2);
    toBeAdd.push_back(v3);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();
    toBeAdd.push_back(v1);
    toBeAdd.push_back(v3);
    toBeAdd.push_back(v4);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();

    v1 = GeomVert(10.0, 0.0, 0.0);
    v2 = GeomVert(20.0, 0.0, 0.0);
    v3 = GeomVert(20.0, 10.0, 0.0);
    v4 = GeomVert(10.0, 10.0, 0.0);

    toBeAdd.push_back(v1);
    toBeAdd.push_back(v2);
    toBeAdd.push_back(v3);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();
    toBeAdd.push_back(v1);
    toBeAdd.push_back(v3);
    toBeAdd.push_back(v4);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();

    OriginalVert oriVert;
    OriginalFace oriFace;
    Subdivision::dooSabinCalcFace(meshIn,meshOut, &oriVert, &oriFace);
    Subdivision::dooSabinCalcEdge(meshIn,meshOut, &oriVert);
    Subdivision::dooSabinCalcVert(meshIn,meshOut, &oriVert, &oriFace);
}


void Test::test3DSB(Mesh *meshIn, Mesh *meshOut){
    vector<GeomVert> toBeAdd;
    GeomVert v1 = GeomVert(0.0, 0.0, 0.0);
    GeomVert v2 = GeomVert(10.0, 0.0, 0.0);
    GeomVert v3 = GeomVert(10.0, 10.0, 0.0);
    GeomVert v4 = GeomVert(0.0, 10.0, 0.0);

    toBeAdd.push_back(v1);
    toBeAdd.push_back(v2);
    toBeAdd.push_back(v3);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();
    toBeAdd.push_back(v1);
    toBeAdd.push_back(v3);
    toBeAdd.push_back(v4);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();

    v1 = GeomVert(0.0, 10.0, 0.0);
    v2 = GeomVert(10.0, 10.0, 0.0);
    v3 = GeomVert(10.0, 20.0, 0.0);
    v4 = GeomVert(0.0, 20.0, 0.0);

    toBeAdd.push_back(v1);
    toBeAdd.push_back(v2);
    toBeAdd.push_back(v3);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();
    toBeAdd.push_back(v1);
    toBeAdd.push_back(v3);
    toBeAdd.push_back(v4);
    meshIn->AddFacet(toBeAdd);
    toBeAdd.clear();

    OriginalVert oriVert;
    OriginalFace oriFace;
    Subdivision::dooSabinCalcFace(meshIn,meshOut, &oriVert, &oriFace);
    Subdivision::dooSabinCalcEdge(meshIn,meshOut, &oriVert);
    Subdivision::dooSabinCalcVert(meshIn,meshOut, &oriVert, &oriFace);
}

void Test::testVanish(Mesh *meshIn)
{
    vector<GeomVert> tobeAdd;
    GeomVert v1 = GeomVert(0.0,0.0,0.0);
    GeomVert v2 = GeomVert(5.0,0.0,0.0);
    GeomVert v3 = GeomVert(0.0,5.0,0.0);
    GeomVert v4 = GeomVert(5.0,5.0,0.0);
    tobeAdd.push_back(v1);
    tobeAdd.push_back(v2);
    tobeAdd.push_back(v4);
    tobeAdd.push_back(v3);
    meshIn->AddFacet(tobeAdd);
    tobeAdd.clear();

    v1 = GeomVert(0.0, 10.0, 0.0);
    v2 = GeomVert(5.0,10.0,0.0);
    tobeAdd.push_back(v3);
    tobeAdd.push_back(v4);
    tobeAdd.push_back(v2);
    tobeAdd.push_back(v1);
    meshIn->AddFacet(tobeAdd);
    tobeAdd.clear();

    v3 = GeomVert(0.0, 15.0, 0.0);
    v4 = GeomVert(5.0,15.0,0.0);
    tobeAdd.push_back(v1);
    tobeAdd.push_back(v2);
    tobeAdd.push_back(v4);
    tobeAdd.push_back(v3);
    meshIn->AddFacet(tobeAdd);
    tobeAdd.clear();

    v1 = GeomVert(5.0, 0.0, 0.0);
    v2 = GeomVert(10.0,0.0,0.0);
    v3 = GeomVert(10.0, 5.0, 0.0);
    v4 = GeomVert(5.0,5.0,0.0);
    tobeAdd.push_back(v1);
    tobeAdd.push_back(v2);
    tobeAdd.push_back(v3);
    tobeAdd.push_back(v4);
    meshIn->AddFacet(tobeAdd);
    tobeAdd.clear();

    v1 = GeomVert(5.0, 10.0, 0.0);
    v2 = GeomVert(10.0,10.0,0.0);
    GeomVert v5 = GeomVert(15.0 , 7.5, 0);
    tobeAdd.push_back(v4);
    tobeAdd.push_back(v3);
    tobeAdd.push_back(v5);
    tobeAdd.push_back(v2);
    tobeAdd.push_back(v1);
    meshIn->AddFacet(tobeAdd);
    tobeAdd.clear();

    v3 = GeomVert(10.0 ,15.0, 0.0);
    v4 = GeomVert(5.0 ,15.0, 0.0);
    tobeAdd.push_back(v1);
    tobeAdd.push_back(v2);
    tobeAdd.push_back(v3);
    tobeAdd.push_back(v4);
    meshIn->AddFacet(tobeAdd);
    tobeAdd.clear();

    v4 = GeomVert(15.0 ,15.0, 0.0);
    tobeAdd.push_back(v2);
    tobeAdd.push_back(v5);
    tobeAdd.push_back(v4);
    tobeAdd.push_back(v3);
    meshIn->AddFacet(tobeAdd);
    tobeAdd.clear();


    v3 = GeomVert(20.0 ,15.0, 0.0);
    v2 = GeomVert(20.0 ,7.5, 0.0);
    tobeAdd.push_back(v5);
    tobeAdd.push_back(v2);
    tobeAdd.push_back(v3);
    tobeAdd.push_back(v4);
    meshIn->AddFacet(tobeAdd);
    tobeAdd.clear();

    v3 = GeomVert(15.0 ,0.0, 0.0);
    v4 = GeomVert(20.0 ,0.0, 0.0);
    tobeAdd.push_back(v5);
    tobeAdd.push_back(v3);
    tobeAdd.push_back(v4);
    tobeAdd.push_back(v2);
    meshIn->AddFacet(tobeAdd);
    tobeAdd.clear();

    v3 = GeomVert(15.0 ,0.0, 0.0);
    v4 = GeomVert(10.0 ,0.0, 0.0);
    v1 = GeomVert(10.0, 5.0, 0);
    tobeAdd.push_back(v1);
    tobeAdd.push_back(v4);
    tobeAdd.push_back(v3);
    tobeAdd.push_back(v5);
    meshIn->AddFacet(tobeAdd);
    tobeAdd.clear();
}
