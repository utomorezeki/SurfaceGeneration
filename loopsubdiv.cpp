#include "loopsubdiv.h"

void LoopSubdiv::calculateEdgeVert(Mesh *meshIn)
{
    for(int i = 0; i < meshIn->GetNumberEdges(); i++){
        TopoEdge currE = meshIn->GetEdge(i);
        TopoFacet oneFace = meshIn->GetFacet(currE.GetIncFacet(0));
        int cV;
        for(int j = 0; j < oneFace.GetNumberVertices(); j++){
            cV = oneFace.GetVertexInd(j);
            if(cV != currE.GetVertex(0) && cV != currE.GetVertex(1))
                break;
        }
        GeomVert v1 = meshIn->GetGeomVertex(currE.GetVertex(0));
        GeomVert v2 = meshIn->GetGeomVertex(currE.GetVertex(1));
        GeomVert otherVert1 = meshIn->GetGeomVertex(cV);
        double aX = 0;
        double aY = 0;
        double aZ = 0;
        int numFaceInc = currE.GetNumberIncFacets();
        if(numFaceInc == 2){
            TopoFacet twoFace = meshIn->GetFacet(currE.GetIncFacet(1));
            int cV2;
            for(int k = 0; k < twoFace.GetNumberVertices(); k++){
                cV2 = twoFace.GetVertexInd(k);
                if(cV2 != currE.GetVertex(0) && cV2 != currE.GetVertex(1))
                    break;
            }
            GeomVert otherVert2 = meshIn->GetGeomVertex(cV2);
            aX = ( (v1.GetCo(0) * 3.0) + (v2.GetCo(0) * 3.0) + otherVert1.GetCo(0) + otherVert2.GetCo(0)) / 8.0;
            aY = ( (v1.GetCo(1) * 3.0) + (v2.GetCo(1) * 3.0) + otherVert1.GetCo(1) + otherVert2.GetCo(1)) / 8.0;
            aZ = ( (v1.GetCo(2) * 3.0) + (v2.GetCo(2) * 3.0) + otherVert1.GetCo(2) + otherVert2.GetCo(2)) / 8.0;
        }
        else {
            aX = ( v1.GetCo(0) + v2.GetCo(0) ) / 2.0;
            aY = ( v1.GetCo(1) + v2.GetCo(1) ) / 2.0;
            aZ = ( v1.GetCo(2) + v2.GetCo(2) ) / 2.0;
        }
        GeomVert addV = GeomVert(aX,aY,aZ);
        edgeOri.addVertex(i,addV);
    }
}

void LoopSubdiv::calculateVertVert(Mesh *meshIn){
    for(int i = 0; i < meshIn->GetNumberVertices(); i++){
        TopoVert currV = meshIn->GetVertex(i);
        double sumVx = 0;
        double sumVy = 0;
        double sumVz = 0;
        int numberAjdV = currV.GetNumberIncEdges();
        for(int j = 0; j < numberAjdV; j++){
            TopoEdge currE = meshIn->GetEdge(currV.GetIncEdge(j));
            GeomVert otherV = meshIn->GetGeomVertex(currE.GetVertex(0));
            if(currE.GetVertex(0) == i)
                otherV = meshIn->GetGeomVertex(currE.GetVertex(1));

            sumVx = sumVx + (otherV.GetCo(0) / numberAjdV);
            sumVy = sumVy + (otherV.GetCo(1) / numberAjdV);
            sumVz = sumVz + (otherV.GetCo(2) / numberAjdV);
        }
        GeomVert currGeomV = meshIn->GetGeomVertex(i);
        double alpha = 0.625;
        double vertVx = (1.0 - alpha) * sumVx + alpha * currGeomV.GetCo(0);
        double vertVy = (1.0 - alpha) * sumVy + alpha * currGeomV.GetCo(1);
        double vertVz = (1.0 - alpha) * sumVz + alpha * currGeomV.GetCo(2);
        GeomVert vertV = GeomVert(vertVx,vertVy,vertVz);
        vertexOri.addVertex(i,vertV);
    }
}

Mesh LoopSubdiv::calculateMesh(Mesh *meshIn)
{
    this->calculateEdgeVert(meshIn);
    this->calculateVertVert(meshIn);
    Mesh retVal;
    for(int i = 0; i < meshIn->GetNumberFacets(); i++){
        TopoFacet currFace = meshIn->GetFacet(i);
        for(int j = 0; j < currFace.GetNumberVertices(); j++){
            TopoVert currV = meshIn->GetVertex(currFace.GetVertexInd(j));
            int eIdx1, k, eIdx2;
            for(k = 0; k < currV.GetNumberIncEdges(); k++){
                eIdx1 = currV.GetIncEdge(k);
                if(eIdx1 == currFace.GetIncEdge(0) || eIdx1 == currFace.GetIncEdge(1) || eIdx1 == currFace.GetIncEdge(2))
                    break;
            }
            for(k = k + 1; k < currV.GetNumberIncEdges(); k++){
                eIdx2 = currV.GetIncEdge(k);
                if(eIdx2 == currFace.GetIncEdge(0) || eIdx2 == currFace.GetIncEdge(1) || eIdx2 == currFace.GetIncEdge(2))
                    break;
            }
            vector<GeomVert> toBeAdd;
            toBeAdd.push_back(vertexOri.getNewVertex(currFace.GetVertexInd(j)));
            toBeAdd.push_back(edgeOri.getNewVertex(eIdx1));
            toBeAdd.push_back(edgeOri.getNewVertex(eIdx2));
            retVal.AddFacet(toBeAdd);
            toBeAdd.clear();
        }
        vector<GeomVert> toBeAddEdges;
        toBeAddEdges.push_back(edgeOri.getNewVertex(currFace.GetIncEdge(0)));
        toBeAddEdges.push_back(edgeOri.getNewVertex(currFace.GetIncEdge(1)));
        toBeAddEdges.push_back(edgeOri.getNewVertex(currFace.GetIncEdge(2)));
        retVal.AddFacet(toBeAddEdges);
        toBeAddEdges.clear();
    }
    return retVal;
}
