#include "catmulloriginal.h"

void CatmullOriginal::addVertex(int originalV, GeomVert newVert)
{
    int idx = listNum.indexOf(originalV);
    if (idx == -1){
        listNum.append(originalV);
        list.push_back(newVert);
    }
    else {
        perror("CATMULL ORIGINAL CALLING IDX TWICE");
    }
}

GeomVert CatmullOriginal::getNewVertex(int originalV){
    int idx = listNum.indexOf(originalV);
    if(idx == -1)
        perror("NO SUCH INDEX");
    return list.at(idx);
}

void CatmullOriginal::clear(){
    list.clear();
    listNum.clear();
}
