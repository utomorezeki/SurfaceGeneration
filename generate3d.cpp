#include "generate3d.h"
#include <cmath>
#include "mesh.h"

#define PI 3.14159265

Polyhedron Gen3D::revCalcFaces(QVector<double> gr_x, QVector<double> gr_y , Mesh *mesh, int revSlices)
{
    Polyhedron retVal = Polyhedron(revSlices, gr_x.size());
    vector<GeomVert> fGV,sGV;
    for (int i = 0; i < gr_x.size() - 1; i++)
    {
        fGV = revCalcCir(revSlices, gr_x.at(i), gr_y.at(i));
        sGV = revCalcCir(revSlices, gr_x.at(i + 1), gr_y.at(i + 1));

        retVal.insertData(fGV);

        for(int j = 0; j < revSlices - 1; j++)
        {
            vector<GeomVert> toBeAdded;
            toBeAdded.push_back(fGV[j]);
            toBeAdded.push_back(fGV[j+1]);
            toBeAdded.push_back(sGV[j]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
            toBeAdded.push_back(sGV[j]);
            toBeAdded.push_back(fGV[j+1]);
            toBeAdded.push_back(sGV[j + 1]);
            mesh->AddFacet(toBeAdded);
        }
        vector<GeomVert> toBeAdded;
        toBeAdded.push_back(fGV[revSlices - 1]);
        toBeAdded.push_back(fGV[0]);
        toBeAdded.push_back(sGV[revSlices - 1]);
        mesh->AddFacet(toBeAdded);
        toBeAdded.clear();
        toBeAdded.push_back(sGV[revSlices - 1]);
        toBeAdded.push_back(fGV[0]);
        toBeAdded.push_back(sGV[0]);
        mesh->AddFacet(toBeAdded);
    }
    retVal.insertData(sGV);
    return retVal;
}

vector<GeomVert> Gen3D::revCalcCir(int revSlices, double xVal, double yVal)
{
    vector<GeomVert> retVal;
    retVal.push_back( GeomVert(xVal, yVal, 0.0) ); //first pt on the ground z=0

    double degreeInterval = 360.0 / revSlices;

    for(int i = 1; i < revSlices; i++)
    {
        double currentDeg = i * degreeInterval;
        double curY = cos(currentDeg * PI / 180) * yVal;
        double curZ = sin(currentDeg * PI / 180) * yVal;
        retVal.push_back( GeomVert(xVal, curY, curZ) );
    }

    return retVal;
}


Polyhedron Gen3D::extCalcFaces(QVector<double> gr_x, QVector<double> gr_y , Mesh *mesh, int extDepth)
{
    Polyhedron retVal = Polyhedron(4,gr_x.size());
    vector<GeomVert> fGV,sGV;
    for (int i = 0; i < gr_x.size() - 1; i++)
    {
        fGV = extCalcPlane(gr_y.at(i), gr_x.at(i), extDepth);
        sGV = extCalcPlane(gr_y.at(i + 1), gr_x.at(i + 1), extDepth);

        retVal.insertData(fGV);

        vector<GeomVert> toBeAdded;
        toBeAdded.push_back(fGV[0]);
        toBeAdded.push_back(fGV[1]);
        toBeAdded.push_back(sGV[0]);
        mesh->AddFacet(toBeAdded);
        toBeAdded.clear();
        toBeAdded.push_back(sGV[0]);
        toBeAdded.push_back(fGV[1]);
        toBeAdded.push_back(sGV[1]);
        mesh->AddFacet(toBeAdded);

        toBeAdded.clear();
        toBeAdded.push_back(fGV[1]);
        toBeAdded.push_back(fGV[2]);
        toBeAdded.push_back(sGV[1]);
        mesh->AddFacet(toBeAdded);
        toBeAdded.clear();
        toBeAdded.push_back(sGV[1]);
        toBeAdded.push_back(fGV[2]);
        toBeAdded.push_back(sGV[2]);
        mesh->AddFacet(toBeAdded);

        toBeAdded.clear();
        toBeAdded.push_back(fGV[2]);
        toBeAdded.push_back(fGV[3]);
        toBeAdded.push_back(sGV[2]);
        mesh->AddFacet(toBeAdded);
        toBeAdded.clear();
        toBeAdded.push_back(sGV[2]);
        toBeAdded.push_back(fGV[3]);
        toBeAdded.push_back(sGV[3]);
        mesh->AddFacet(toBeAdded);
    }
    retVal.insertData(sGV);
    return retVal;
}

vector<GeomVert> Gen3D::extCalcPlane(double yVal, double xVal, int extDepth)
{
     vector<GeomVert> retVal;
     GeomVert vert = GeomVert(xVal,yVal,0.0);
     retVal.push_back(vert);
     vert = GeomVert(xVal, yVal + (1.0/3) * yVal,(double)extDepth / 3.0);
     retVal.push_back(vert);
     vert = GeomVert(xVal, yVal + (1.0/3) * yVal,(double)extDepth / 3.0 *2);
     retVal.push_back(vert);
     vert = GeomVert(xVal,yVal,(double)extDepth);
     retVal.push_back(vert);
     return retVal;
}

void Gen3D::sweepCalcFaces(QVector<double> gr_x, QVector<double> gr_y ,QVector<double> gr2_x, QVector<double> gr2_y, Mesh *mesh) //gr2_x is z axis && gr2_y is y axis
{
    for (int i = 0; i < gr_x.size() - 1; i++)
    {
        vector<GeomVert> fGV,sGV;
        fGV = sweepCalcPlane(gr_y.at(i), gr_x.at(i), gr2_x, gr2_y);

        sGV = sweepCalcPlane(gr_y.at(i + 1), gr_x.at(i + 1), gr2_x, gr2_y);

        for(int j = 0; j < fGV.size() - 1; j++)
        {
            vector<GeomVert> toBeAdded;
            toBeAdded.push_back(fGV[j]);
            toBeAdded.push_back(fGV[j+1]);
            toBeAdded.push_back(sGV[j]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
            toBeAdded.push_back(sGV[j]);
            toBeAdded.push_back(fGV[j+1]);
            toBeAdded.push_back(sGV[j + 1]);
            mesh->AddFacet(toBeAdded);
        }
    }
}

vector<GeomVert> Gen3D::sweepCalcPlane(double yVal, double xVal, QVector<double> gr2_z, QVector<double> gr2_y)
{
     vector<GeomVert> retVal;
     GeomVert vert = GeomVert(xVal,yVal,0.0);
     retVal.push_back(vert);

     double initZ = gr2_z.at(0);
     double initY = gr2_y.at(0);
     for (int n = 1; n < gr2_z.size(); n++)
     {
         vert = GeomVert(xVal,yVal + (gr2_y.at(n) - initY),gr2_z.at(n) - initZ);
         retVal.push_back(vert);
     }
     return retVal;
}

void Gen3D::extBezCalcMesh(Mesh *mesh, Polyhedron poly, double uInt, double vInt, int revExt)
{
    for (double curV = 0; curV < 1.0 - vInt ; curV+=vInt)
    {
        vector<GeomVert> fGV,sGV;
        fGV = extBezCalcPlane(poly,uInt,curV);
        sGV = extBezCalcPlane(poly,uInt,curV + vInt);
        vector<GeomVert> toBeAdded;

        for(int j = 0; j < fGV.size() - 1; j++)
        {
            toBeAdded.push_back(fGV[j]);
            toBeAdded.push_back(fGV[j+1]);
            toBeAdded.push_back(sGV[j]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
            toBeAdded.push_back(sGV[j]);
            toBeAdded.push_back(fGV[j+1]);
            toBeAdded.push_back(sGV[j + 1]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
        }
        if (revExt){
            int j = fGV.size() - 1;
            toBeAdded.push_back(fGV[j]);
            toBeAdded.push_back(fGV[0]);
            toBeAdded.push_back(sGV[j]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
            toBeAdded.push_back(sGV[j]);
            toBeAdded.push_back(fGV[0]);
            toBeAdded.push_back(sGV[0]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
        }
    }
}

vector<GeomVert> Gen3D::extBezCalcPlane(Polyhedron poly, double uInt, double curV)
{
    vector<GeomVert> retVal;
    for(double uVal = 0; uVal < 1.0; uVal += uInt){
        QVector<double> Bcol = Mathematics::calcBernstein(poly.getCol(),curV);
        QVector<double> Brow = Mathematics::calcBernstein(poly.getRow(),uVal);
        double pValX,pValY,pValZ;
        pValX = 0;
        pValY = 0;
        pValZ = 0;
        for(int i=0; i < poly.getRow(); i++)
        {
            for(int j = 0; j < poly.getCol(); j++)
            {
                GeomVert polyhedronVertex = poly.getData(i,j);
                pValX = pValX + polyhedronVertex.GetCo(0) * Brow.at(i) * Bcol.at(j);
                pValY = pValY + polyhedronVertex.GetCo(1) * Brow.at(i) * Bcol.at(j);
                pValZ = pValZ + polyhedronVertex.GetCo(2) * Brow.at(i) * Bcol.at(j);
            }
        }
        GeomVert pVal = GeomVert(pValX,pValY,pValZ);
        retVal.push_back(pVal);
    }
    return retVal;
}

void Gen3D::extCBBSCalcMesh(Mesh *mesh, Polyhedron poly, double uInt, double vInt, int revExt)
{
    for (double curV = 0; curV < 1.0 - vInt ; curV+=vInt)
    {
        vector<GeomVert> fGV,sGV;
        fGV = extCBBSCalcPlane(poly,uInt,curV);
        sGV = extCBBSCalcPlane(poly,uInt,curV + vInt);
        vector<GeomVert> toBeAdded;
        for(int j = 0; j < fGV.size() - 1; j++)
        {

            toBeAdded.push_back(fGV[j]);
            toBeAdded.push_back(fGV[j+1]);
            toBeAdded.push_back(sGV[j]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
            toBeAdded.push_back(sGV[j]);
            toBeAdded.push_back(fGV[j+1]);
            toBeAdded.push_back(sGV[j + 1]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
        }
        if (revExt){
            int j = fGV.size() - 1;
            toBeAdded.push_back(fGV[j]);
            toBeAdded.push_back(fGV[0]);
            toBeAdded.push_back(sGV[j]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
            toBeAdded.push_back(sGV[j]);
            toBeAdded.push_back(fGV[0]);
            toBeAdded.push_back(sGV[0]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
        }
    }
}

vector<GeomVert> Gen3D::extCBBSCalcPlane(Polyhedron poly, double uInt, double curV)
{
    vector<GeomVert> retVal;
    for(double uVal = 0; uVal < 1.0; uVal += uInt){
        QVector<int> tCol = Mathematics::calcT(poly.getCol());
        QVector<int> tRow = Mathematics::calcT(poly.getRow());
        QVector<double> NCol = Mathematics::calcN4s(curV,tCol);
        QVector<double> NRow = Mathematics::calcN4s(uVal,tRow);
        double pValX,pValY,pValZ;
        pValX = 0;
        pValY = 0;
        pValZ = 0;
        for(int i=0; i < poly.getRow(); i++)
        {
            for(int j = 0; j < poly.getCol(); j++)
            {
                GeomVert polyhedronVertex = poly.getData(i,j);
                pValX = pValX + polyhedronVertex.GetCo(0) * NRow.at(i) * NCol.at(j);
                pValY = pValY + polyhedronVertex.GetCo(1) * NRow.at(i) * NCol.at(j);
                pValZ = pValZ + polyhedronVertex.GetCo(2) * NRow.at(i) * NCol.at(j);
            }
        }
        GeomVert pVal = GeomVert(pValX,pValY,pValZ);
        retVal.push_back(pVal);
    }
    return retVal;
}
