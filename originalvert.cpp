#include "originalvert.h"

void OriginalVert::addVertex(int originalV, GeomVert newVert)
{
    int idx = listNum.indexOf(originalV);
    if (idx == -1){
        listNum.append(originalV);
        vector<GeomVert> newList;
        newList.push_back(newVert);
        list.append(newList);
    }
    else {
        vector<GeomVert> *modList = list.data();
        modList[idx].push_back(newVert);
    }
}

vector<GeomVert> OriginalVert::getVertexList(int originalV){
    int idx = listNum.indexOf(originalV);
    if(idx == -1)
        perror("NO SUCH INDEX");
    return list.at(idx);
}


