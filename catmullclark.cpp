#include "catmullclark.h"

void CatmullClark::findFaceVert(Mesh *meshIn)
{
    for(int i = 0; i < meshIn->GetNumberFacets(); i++){
        TopoFacet currFace = meshIn->GetFacet(i);
        double fVx = 0;
        double fVy = 0;
        double fVz = 0;
        int numVert = currFace.GetNumberVertices();
        for(int j = 0; j < numVert; j++){
            GeomVert currV = meshIn->GetGeomVertex(currFace.GetVertexInd(j));
            fVx = fVx + currV.GetCo(0) / numVert;
            fVy = fVy + currV.GetCo(1) / numVert;
            fVz = fVz + currV.GetCo(2) / numVert;
        }
        GeomVert faceVert = GeomVert(fVx,fVy,fVz);
        faceOri.addVertex(i,faceVert);
    }
}


void CatmullClark::findEdgeVert(Mesh *meshIn)
{
    for(int i = 0; i < meshIn->GetNumberEdges(); i++){
        TopoEdge currEdge = meshIn->GetEdge(i);

        GeomVert v1 = meshIn->GetGeomVertex(currEdge.GetVertex(0));
        GeomVert v2 = meshIn->GetGeomVertex(currEdge.GetVertex(1));
        GeomVert vF1 = faceOri.getNewVertex(currEdge.GetIncFacet(0));
        if(currEdge.GetNumberIncFacets() == 1){
            double fVx = (v1.GetCo(0) + v2.GetCo(0)+ vF1.GetCo(0) )/3;
            double fVy = (v1.GetCo(1) + v2.GetCo(1)+ vF1.GetCo(1) )/3;
            double fVz = (v1.GetCo(2) + v2.GetCo(2)+ vF1.GetCo(2) )/3;
            GeomVert edgeVert = GeomVert(fVx,fVy,fVz);
            edgeOri.addVertex(i,edgeVert);
            continue;
        }
        GeomVert vF2 = faceOri.getNewVertex(currEdge.GetIncFacet(1));
        double fVx = (v1.GetCo(0) + v2.GetCo(0)+ vF1.GetCo(0) + vF2.GetCo(0))/4;
        double fVy = (v1.GetCo(1) + v2.GetCo(1)+ vF1.GetCo(1) + vF2.GetCo(1))/4;
        double fVz = (v1.GetCo(2) + v2.GetCo(2)+ vF1.GetCo(2) + vF2.GetCo(2))/4;
        GeomVert edgeVert = GeomVert(fVx,fVy,fVz);
        edgeOri.addVertex(i,edgeVert);
    }
}

void CatmullClark::findVertexVert(Mesh *meshIn){
    for(int i = 0; i < meshIn->GetNumberVertices(); i++){
        TopoVert currVert = meshIn->GetVertex(i);
        double Qx = 0;
        double Qy = 0;
        double Qz = 0;
        int faceIncident = currVert.GetNumberIncFacets();
        for(int j = 0; j < faceIncident; j++){
            GeomVert faceVrtx = faceOri.getNewVertex(currVert.GetIncFacet(j));
            Qx = Qx + (faceVrtx.GetCo(0) / faceIncident);
            Qy = Qy + (faceVrtx.GetCo(1) / faceIncident);
            Qz = Qz + (faceVrtx.GetCo(2) / faceIncident);
        }
        GeomVert Qv = GeomVert(Qx,Qy,Qz);

        double Rx = 0;
        double Ry = 0;
        double Rz = 0;
        int edgeIncident = currVert.GetNumberIncEdges();
        for(int j = 0; j < edgeIncident; j++){
            TopoEdge cEdge = meshIn->GetEdge(currVert.GetIncEdge(j));
            GeomVert cv1 = meshIn->GetGeomVertex(cEdge.GetVertex(0));
            GeomVert cv2 = meshIn->GetGeomVertex(cEdge.GetVertex(1));
            double mx = (cv1.GetCo(0) + cv2.GetCo(0)) / 2;
            double my = (cv1.GetCo(1) + cv2.GetCo(1)) / 2;
            double mz = (cv1.GetCo(2) + cv2.GetCo(2)) / 2;
            GeomVert mid = GeomVert(mx,my,mz);
            Rx = Rx + (mid.GetCo(0) / edgeIncident);
            Ry = Ry + (mid.GetCo(1) / edgeIncident);
            Rz = Rz + (mid.GetCo(2) / edgeIncident);
        }
        GeomVert Rv = GeomVert(Rx,Ry,Rz);
        GeomVert currGV = meshIn->GetGeomVertex(i);
        double vertX = (1.0 / edgeIncident) * Qv.GetCo(0) + (1.0/edgeIncident) * Rv.GetCo(0) + (((double)edgeIncident - 2.0) / edgeIncident) * currGV.GetCo(0);
        double vertY = (1.0 / edgeIncident) * Qv.GetCo(1) + (1.0/edgeIncident) * Rv.GetCo(1) + (((double)edgeIncident - 2.0) / edgeIncident) * currGV.GetCo(1);;
        double vertZ = (1.0 / edgeIncident) * Qv.GetCo(2) + (1.0/edgeIncident) * Rv.GetCo(2) + (((double)edgeIncident - 2.0) / edgeIncident) * currGV.GetCo(2);;
        GeomVert vertexVertex = GeomVert(vertX,vertY,vertZ);
        vertexOri.addVertex(i,vertexVertex);
    }
}

void CatmullClark::generateFaces(Mesh *meshIn)
{
    for(int i = 0; i < meshIn->GetNumberFacets(); i++){
        TopoFacet currFace = meshIn->GetFacet(i);
        GeomVert faceV = faceOri.getNewVertex(i);
        for(int j = 0; j < currFace.GetNumberEdges(); j++){
            TopoEdge currEdge = meshIn->GetEdge(currFace.GetIncEdge(j));
            GeomVert currEdgeVert = edgeOri.getNewVertex(currFace.GetIncEdge(j));
            GeomVert currVertVert1 = vertexOri.getNewVertex(currEdge.GetVertex(0));
            GeomVert currVertVert2 = vertexOri.getNewVertex(currEdge.GetVertex(1));
            for(int k = j + 1; k < currFace.GetNumberEdges(); k++){
                TopoEdge otherCurrEdge = meshIn->GetEdge(currFace.GetIncEdge(k));
                GeomVert otherCurrEdgeVert = edgeOri.getNewVertex(currFace.GetIncEdge(k));
                GeomVert otherCurrVertVert1 = vertexOri.getNewVertex(otherCurrEdge.GetVertex(0));
                GeomVert otherCurrVertVert2 = vertexOri.getNewVertex(otherCurrEdge.GetVertex(1));
                if (otherCurrVertVert1 == currVertVert1){
                    vector<GeomVert> toBeAdd;
                    toBeAdd.push_back(faceV);
                    toBeAdd.push_back(otherCurrEdgeVert);
                    toBeAdd.push_back(currVertVert1);
                    toBeAdd.push_back(currEdgeVert);
                    subdivMesh.AddFacet(toBeAdd);
                } else if (otherCurrVertVert1 == currVertVert2){
                    vector<GeomVert> toBeAdd;
                    toBeAdd.push_back(faceV);
                    toBeAdd.push_back(otherCurrEdgeVert);
                    toBeAdd.push_back(currVertVert2);
                    toBeAdd.push_back(currEdgeVert);
                    subdivMesh.AddFacet(toBeAdd);
                } else if (otherCurrVertVert2 == currVertVert1){
                    vector<GeomVert> toBeAdd;
                    toBeAdd.push_back(faceV);
                    toBeAdd.push_back(otherCurrEdgeVert);
                    toBeAdd.push_back(currVertVert1);
                    toBeAdd.push_back(currEdgeVert);
                    subdivMesh.AddFacet(toBeAdd);
                } else if (otherCurrVertVert2 == currVertVert2){
                    vector<GeomVert> toBeAdd;
                    toBeAdd.push_back(faceV);
                    toBeAdd.push_back(otherCurrEdgeVert);
                    toBeAdd.push_back(currVertVert2);
                    toBeAdd.push_back(currEdgeVert);
                    subdivMesh.AddFacet(toBeAdd);
                }
            }
        }
    }
}

Mesh CatmullClark::generateMesh(Mesh *meshIn)
{
    findFaceVert(meshIn);
    findEdgeVert(meshIn);
    findVertexVert(meshIn);
    generateFaces(meshIn);
    return subdivMesh;
}
