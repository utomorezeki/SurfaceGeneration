#include "polyhedron.h"

void Polyhedron::insertData(GeomVert dataIn){
    data.push_back(dataIn);
}

void Polyhedron::insertData(vector<GeomVert> dataIn){
    for(int n = 0; n < dataIn.size(); n++)
        data.push_back(dataIn.at(n));
}

GeomVert Polyhedron::getData(int rowD, int colD){

    return(data.at( row * colD + rowD));
}
