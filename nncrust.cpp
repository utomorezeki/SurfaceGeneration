#include "nncrust.h"
#include <QDebug>
#include <cmath>
#include <qvector2d.h>

void NNCrust::initial()
{
    vector<Point> points;
    points.push_back(Point(10,10));   // first point
    points.push_back(Point(60,10));   // second point
    points.push_back(Point(30,40));   // third point
    points.push_back(Point(40,40));
    points.push_back(Point(50,0));
    points.push_back(Point(15,0));

    Delaunay dt;
    dt.insert(points.begin(),points.end());

    vector<GeomVert> tobeAdd;

    Point dummy;
    for (Face_iterator fit = dt.faces_begin();
            fit != dt.faces_end();
            ++fit)
    {

         //qDebug() << "FACE CIRCUMCENTER: "  << dualTest.x() << dualTest.y();
         dummy = fit->vertex(0)->point();
         GeomVert add1 = GeomVert(dummy.x(),dummy.y(),0.0);
         tobeAdd.push_back(add1);
         //qDebug() << "POINT 1: "  << dummy.x() << dummy.y();
         dummy = fit->vertex(1)->point();
         //qDebug() << "POINT 2: "  << dummy.x() << dummy.y();
         GeomVert add2 = GeomVert(dummy.x(),dummy.y(),0.0);
         tobeAdd.push_back(add2);
         dummy = fit->vertex(2)->point();
         //qDebug() << "POINT 3: "  << dummy.x() << dummy.y();

         GeomVert add3 = GeomVert(dummy.x(),dummy.y(),0.0);
         tobeAdd.push_back(add3);
         saved.AddFacet(tobeAdd);
         tobeAdd.clear();
    }
}

double NNCrust::rangeMht(GeomVert A, GeomVert B)
{
    QVector2D AVec = QVector2D(A.GetCo(0),A.GetCo(1));
    QVector2D BVec = QVector2D(B.GetCo(0),B.GetCo(1));
    QVector2D fVec = BVec - AVec;
    return (double)fVec.length();
}

bool NNCrust::angleQual(int vert, int e1, int e2)
{
    GeomVert centerV = saved.GetGeomVertex(vert);
    TopoEdge edge1 = saved.GetEdge(e1);
    TopoEdge edge2 = saved.GetEdge(e2);
    GeomVert OVe1 = saved.GetGeomVertex(edge1.GetVertex(0));
    if (OVe1 == centerV)
        OVe1 = saved.GetGeomVertex(edge1.GetVertex(1));
    GeomVert OVe2 = saved.GetGeomVertex(edge2.GetVertex(0));
    if (OVe2 == centerV)
        OVe2 = saved.GetGeomVertex(edge2.GetVertex(1));
    QVector2D oriVec = QVector2D(centerV.GetCo(0),centerV.GetCo(1));
    QVector2D o1Vec = QVector2D(OVe1.GetCo(0),OVe1.GetCo(1));
    QVector2D o2Vec = QVector2D(OVe2.GetCo(0),OVe2.GetCo(1));
    QVector2D fVec1 = o1Vec - oriVec;
    QVector2D fVec2 = o2Vec - oriVec;
    float dpr = QVector2D::dotProduct(fVec1,fVec2);
    if (dpr >= 0)
        return false;
    return true;
}

void NNCrust::pickEdges()
{
    int numVert = saved.GetNumberVertices();
    for(int i=0; i < numVert; i++){
        TopoVert currV = saved.GetVertex(i);
        int numEdges = currV.GetNumberIncEdges();
        TopoEdge currE = saved.GetEdge(currV.GetIncEdge(0));
        double minMag = rangeMht(saved.GetGeomVertex(currE.GetVertex(0)),saved.GetGeomVertex(currE.GetVertex(1)));
        int minE = 0;
        for (int j = 1; j < numEdges; j++)
        {
            currE = saved.GetEdge(currV.GetIncEdge(j));
            double mag = rangeMht(saved.GetGeomVertex(currE.GetVertex(0)),saved.GetGeomVertex(currE.GetVertex(1)));
            if(mag < minMag){
                minMag = mag;
                minE = j;
            }
        }
        vector<int> qualDeg;
        for (int j = 0; j < numEdges; j++)
        {
            if(j == minE)
                continue;
            if(angleQual(i,currV.GetIncEdge(minE),currV.GetIncEdge(j))){
                //qDebug() << "VERT: " << i;
                //qDebug() << "MinE: " << currV.GetIncEdge(minE);
                //qDebug() << "OE: " << currV.GetIncEdge(j);
                qualDeg.push_back(j);
            }
        }
        currE = saved.GetEdge(currV.GetIncEdge(qualDeg[0]));
        minMag = rangeMht(saved.GetGeomVertex(currE.GetVertex(0)),saved.GetGeomVertex(currE.GetVertex(1)));
        int minE2 = qualDeg[0];
        for(int j = 1; j < qualDeg.size(); j++){
            currE = saved.GetEdge(currV.GetIncEdge(qualDeg[j]));
            double mag = rangeMht(saved.GetGeomVertex(currE.GetVertex(0)),saved.GetGeomVertex(currE.GetVertex(1)));
            if(mag < minMag){
                minMag = mag;
                minE2 = qualDeg[j];
            }
        }
        inclEdges.insert(currV.GetIncEdge(minE));
        inclEdges.insert(currV.GetIncEdge(minE2));
    }

}

void NNCrust::traverseE()
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
    for (std::vector<int>::iterator it3=vOrder.begin(); it3!=vOrder.end(); ++it3)
        qDebug() << ' ' << *it3;
}

Mesh NNCrust::getM(){
    return saved;
}
