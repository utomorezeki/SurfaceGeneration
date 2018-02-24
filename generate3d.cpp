#include "generate3d.h"
#include <cmath>
#include "mesh.h"

void Gen3D::revCalcFaces(QVector<double> gr_x, QVector<double> gr_y , Mesh *mesh)
{
    for (int i = 0; i < gr_x.size() - 1; i++)
    {
        vector<GeomVert> fGV,sGV;
        double interval = gr_y.at(i) / 5;
        fGV = revCalcCir(interval, gr_x.at(i));

        double secInterval = gr_y.at(i + 1) / 5;
        sGV = revCalcCir(secInterval, gr_x.at(i + 1));

        for(int j = 0; j < 19; j++)
        {
            vector<GeomVert> toBeAdded;
            toBeAdded.push_back(fGV[j]);
            toBeAdded.push_back(fGV[j+1]);
            toBeAdded.push_back(sGV[j]);
            mesh->AddFacet(toBeAdded);
            toBeAdded.clear();
            toBeAdded.push_back(sGV[j]);
            toBeAdded.push_back(sGV[j + 1]);
            toBeAdded.push_back(fGV[j+1]);
            mesh->AddFacet(toBeAdded);
        }
        vector<GeomVert> toBeAdded;
        toBeAdded.push_back(fGV[19]);
        toBeAdded.push_back(fGV[0]);
        toBeAdded.push_back(sGV[19]);
        mesh->AddFacet(toBeAdded);
        toBeAdded.clear();
        toBeAdded.push_back(sGV[19]);
        toBeAdded.push_back(sGV[0]);
        toBeAdded.push_back(fGV[0]);
        mesh->AddFacet(toBeAdded);
    }
}

vector<GeomVert> Gen3D::revCalcCir(double interval, double xVal)
{
    double radius = pow(interval * 5, 2.0);
    vector<GeomVert> retVal;
    QVector<double> yVal, zVal;
    for(int i = 0; i < 11; i++)
    {
        yVal.append(interval * (i - 5));
        if (i < 6)
            zVal.append(sqrt(radius - pow(yVal.at(i), 2.0)));
        else if (i == 10)
            zVal.insert(0, (-1) * yVal.at(10));
        else
            zVal.insert(i - 6, (-1) * sqrt(radius - pow(yVal.at(i), 2.0)));
    }
    //INSERTING TOP HALF
    for(int i = 0; i < 10; i++)
    {
        if (i < 6)
            retVal.push_back( GeomVert(xVal, yVal.at(10- i), zVal.at(5 + i)) );
        else
            retVal.push_back( GeomVert(xVal, yVal.at(10- i), zVal.at(15 - i)) );
    }
    //INSERT BOT HALF
    for(int i = 0; i < 10; i++)
    {
        if (i < 6)
            retVal.push_back( GeomVert(xVal, yVal.at(i), zVal.at(5 - i)) );
        else
            retVal.push_back( GeomVert(xVal, yVal.at(i), zVal.at(i - 5)) );
    }

    return retVal;
}


void Gen3D::extCalcFaces(QVector<double> gr_x, QVector<double> gr_y , Mesh *mesh)
{
    for (int i = 0; i < gr_x.size() - 1; i++)
    {
        vector<GeomVert> fGV,sGV;
        fGV = extCalcPlane(gr_y.at(i), gr_x.at(i));
        sGV = extCalcPlane(gr_y.at(i + 1), gr_x.at(i + 1));

        vector<GeomVert> toBeAdded;
        toBeAdded.push_back(fGV[0]);
        toBeAdded.push_back(fGV[1]);
        toBeAdded.push_back(sGV[0]);
        mesh->AddFacet(toBeAdded);
        toBeAdded.clear();
        toBeAdded.push_back(sGV[0]);
        toBeAdded.push_back(sGV[1]);
        toBeAdded.push_back(fGV[1]);
        mesh->AddFacet(toBeAdded);
    }
}

vector<GeomVert> Gen3D::extCalcPlane(double yVal, double xVal)
{
     vector<GeomVert> retVal;
     GeomVert vert = GeomVert(xVal,yVal,0.0);
     retVal.push_back(vert);
     vert = GeomVert(xVal,yVal,300.0);
     retVal.push_back(vert);
     return retVal;
}
