#include "originalface.h"

void OriginalFace::addVertex(int originalF, GeomVert newVert)
{
    int idx = faceList.indexOf(originalF);
    if (idx == -1){
        faceList.append(originalF);
        vector<GeomVert> newFaceVertList;
        newFaceVertList.push_back(newVert);
        faceVertexlist.append(newFaceVertList);
    }
    else {
        vector<GeomVert> *modifyList = faceVertexlist.data();
        modifyList[idx].push_back(newVert);
    }
}

bool OriginalFace::checkVertex(int originalF, GeomVert check)
{
     int idx = faceList.indexOf(originalF);
     if (idx == -1){
         perror("no such face, no vertex!");
     }
    vector<GeomVert> iterate = faceVertexlist.at(idx);
    for(int i = 0; i < iterate.size(); i ++){
        if(iterate.at(i) == check)
            return true;
    }
    return false;
}

bool OriginalFace::checkCommon(int faceNum, TopoVert currVert, vector<int> prevFidxes){
    for(int i = 0; i < currVert.GetNumberIncFacets(); i++){
        if(currVert.GetIncFacet(i) == faceNum){
            for(int j = 0; j < prevFidxes.size(); j++){
                if(faceNum == prevFidxes.at(j))
                    return false;
            }
            return true;
        }
    }
    return false;
}

GeomVert OriginalFace::checkMember(vector<GeomVert> faceV, vector<GeomVert> vertV){
    for(int i = 0; i < vertV.size(); i++){
        GeomVert cV = vertV.at(i);
        for(int j = 0; j < faceV.size(); j++){
            if (cV == faceV.at(j))
                return cV;
        }
    }
    perror("nothing in common");
    return GeomVert(0,0,0);
}

vector<GeomVert> OriginalFace::getVList(int originalF)
{
    int idx = faceList.indexOf(originalF);
    if(idx == -1)
        perror("NO SUCH INDEX");
    return faceVertexlist.at(idx);
}
