#ifndef CRUST_H
#define CRUST_H
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Simple_cartesian.h>
#include "mesh.h"
#include <QVector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef K::Point_2 Point;
typedef Delaunay::Face_iterator Face_iterator;

class Crust
{
public:
    void test();
    vector<GeomVert> construct(QVector<double> qv_x, QVector<double> qv_y);
    double rangeMht(GeomVert A, GeomVert B);
    bool angleQual(int vert, int e1, int e2);
    void pickEdges();
    vector<int> traverseE();
private:
    Mesh saved;
    std::set<int> inclEdges;
    vector<GeomVert> oriPts;
    bool inOri(GeomVert check);
};


#endif // CRUST_H
