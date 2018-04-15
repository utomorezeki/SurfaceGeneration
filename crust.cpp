#include "crust.h"
#include <QDebug>
#include <cmath>

void Crust::test()
{
    vector<Point> points;
    points.push_back(Point(10,10));   // first point
    points.push_back(Point(60,10));   // second point
    points.push_back(Point(30,40));   // third point
    points.push_back(Point(40,40));
    points.push_back(Point(50,0));
    points.push_back(Point(15,0));

    oriPts.push_back(GeomVert(10,10,0));   // first point
    oriPts.push_back(GeomVert(60,10,0));   // second point
    oriPts.push_back(GeomVert(30,40,0));   // third point
    oriPts.push_back(GeomVert(40,40,0));
    oriPts.push_back(GeomVert(50,0,0));
    oriPts.push_back(GeomVert(15,0,0));

    Delaunay dt;
    dt.insert(points.begin(),points.end());

    for (Face_iterator fit = dt.faces_begin();
            fit != dt.faces_end();
            ++fit)
    {
        points.push_back(dt.dual(fit));
    }

    Delaunay dft;
    dft.insert(points.begin(),points.end());
    vector<GeomVert> tobeAdd;
    Point dummy;
    for (Face_iterator fit = dft.faces_begin();
            fit != dft.faces_end();
            ++fit)
    {
         dummy = fit->vertex(0)->point();
         GeomVert add1 = GeomVert(dummy.x(),dummy.y(),0.0);
         tobeAdd.push_back(add1);

         dummy = fit->vertex(1)->point();
         GeomVert add2 = GeomVert(dummy.x(),dummy.y(),0.0);
         tobeAdd.push_back(add2);

         dummy = fit->vertex(2)->point();
         GeomVert add3 = GeomVert(dummy.x(),dummy.y(),0.0);
         tobeAdd.push_back(add3);
         saved.AddFacet(tobeAdd);
         tobeAdd.clear();
    }
}

void Crust::pickEdges()
{
    int numE = saved.GetNumberEdges();
    for(int i = 0; i < numE; i++)
    {
        TopoEdge currE = saved.GetEdge(i);
        if(!inOri(saved.GetGeomVertex(currE.GetVertex(0))))
            continue;
        if(!inOri(saved.GetGeomVertex(currE.GetVertex(1))))
            continue;
        inclEdges.insert(i);
    }
}

bool Crust::inOri(GeomVert check)
{
    for(int i = 0; i < oriPts.size(); i++){
        if(oriPts[i] == check)
            return true;
    }
    return false;
}

vector<int> Crust::traverseE()
{
    std::set<int>::iterator it=inclEdges.begin();
    int startE = *it;
    int vS = saved.GetEdge(startE).GetVertex(0);
    int vN = saved.GetEdge(startE).GetVertex(1);
    inclEdges.erase(startE);
    vector<int> vOrder;
    vOrder.push_back(vS);

    int totalSz = inclEdges.size();
    for(int i=0; i < totalSz; i++){
        int rem;
        for(std::set<int>::iterator itIn=inclEdges.begin(); itIn!=inclEdges.end();itIn++)
        {
            int currE = *itIn;
            int vE1 = saved.GetEdge(currE).GetVertex(0);
            int vE2 = saved.GetEdge(currE).GetVertex(1);
            if(vE1 != vN && vE2 != vN)
                continue;
            vOrder.push_back(vN);
            if(vN == vE1)
                vN = vE2;
            else
                vN = vE1;
            rem = currE;
            break;
        }
        inclEdges.erase(rem);
    }
    vOrder.push_back(vS);
    return vOrder;
}

vector<GeomVert> Crust::construct(QVector<double> qv_x, QVector<double> qv_y)
{
    vector<Point> points;
    for(int i = 0; i < qv_x.size(); i++){
        points.push_back(Point(qv_x.at(i),qv_y.at(i)));
        oriPts.push_back(GeomVert(qv_x.at(i),qv_y.at(i),0));
    }

    Delaunay dt;
    dt.insert(points.begin(),points.end());

    for (Face_iterator fit = dt.faces_begin();
            fit != dt.faces_end();
            ++fit)
    {
        points.push_back(dt.dual(fit));
    }

    Delaunay dft;
    dft.insert(points.begin(),points.end());
    vector<GeomVert> tobeAdd;
    Point dummy;
    for (Face_iterator fit = dft.faces_begin();
            fit != dft.faces_end();
            ++fit)
    {
         dummy = fit->vertex(0)->point();
         GeomVert add1 = GeomVert(dummy.x(),dummy.y(),0.0);
         tobeAdd.push_back(add1);

         dummy = fit->vertex(1)->point();
         GeomVert add2 = GeomVert(dummy.x(),dummy.y(),0.0);
         tobeAdd.push_back(add2);

         dummy = fit->vertex(2)->point();
         GeomVert add3 = GeomVert(dummy.x(),dummy.y(),0.0);
         tobeAdd.push_back(add3);
         saved.AddFacet(tobeAdd);
         tobeAdd.clear();
    }
    pickEdges();
    vector<int> vOrd = traverseE();
    vector<GeomVert> retVal;
    for(int i = 0; i < vOrd.size(); i++){
        GeomVert cV = saved.GetGeomVertex(vOrd[i]);
        retVal.push_back(cV);
    }
    return retVal;
}
