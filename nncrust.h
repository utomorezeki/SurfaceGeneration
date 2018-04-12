#ifndef NNCRUST_H
#define NNCRUST_H
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Simple_cartesian.h>
#include "mesh.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef K::Point_2 Point;
typedef Delaunay::Face_iterator Face_iterator;

class NNCrust
{
public:
    void initial();
    Mesh getM();
    double rangeMht(GeomVert A, GeomVert B);
    bool angleQual(int vert, int e1, int e2);
    void pickEdges();
    void traverseE();
private:
    Mesh saved;
    std::set<int> inclEdges;
};

#endif // NNCRUST_H
