#include "subdivision.h"

void Subdivision::dooSabinCalcFace(Mesh *meshIn, Mesh *meshOut, OriginalVert *oriVert, OriginalFace *oriFace)
{
    for(int i = 0; i < meshIn->GetNumberFacets(); i++)
    {
        TopoFacet currFace = meshIn->GetFacet(i);
        vector<GeomVert> vf;
        GeomVert centroid = getCentroid(currFace, meshIn);
        for(int j = 0; j < currFace.GetNumberVertices(); j++)
        {
            TopoVert currTopoVert  = meshIn->GetVertex(currFace.GetVertexInd(j));
            GeomVert currVert = meshIn->GetGeomVertex(currFace.GetVertexInd(j));
            int k,topoEdgeOneVert,topoEdgeTwoVert;
            bool foundOne = false;
            for (k = 0; !foundOne && k < currTopoVert.GetNumberIncEdges(); k++) //get first adj edge
            {
                topoEdgeOneVert = currTopoVert.GetIncEdge(k);
                for(int l = 0; l < currFace.GetNumberEdges(); l++)
                {
                    if(currFace.GetIncEdge(l) == topoEdgeOneVert)
                    {
                        foundOne = true;
                        break;
                    }
                }
            }
            foundOne = false;
            for(k; !foundOne &&k < currTopoVert.GetNumberIncEdges(); k++) // get second ajd edge
            {
                topoEdgeTwoVert = currTopoVert.GetIncEdge(k);
                for(int l = 0; l < currFace.GetNumberEdges(); l++)
                {
                    if(currFace.GetIncEdge(l) == topoEdgeTwoVert)
                    {
                        foundOne = true;
                        break;
                    }
                }
            }
            TopoEdge edge1 = meshIn->GetEdge(topoEdgeOneVert);
            TopoEdge edge2 = meshIn->GetEdge(topoEdgeTwoVert);
            GeomVert otherEdge1 = meshIn->GetGeomVertex(edge1.GetVertex(0));
            if(otherEdge1 == currVert)
                otherEdge1 = meshIn->GetGeomVertex(edge1.GetVertex(1));
            GeomVert otherEdge2 = meshIn->GetGeomVertex(edge2.GetVertex(0));
            if(otherEdge2 == currVert)
                otherEdge2 = meshIn->GetGeomVertex(edge2.GetVertex(1));
            GeomVert midE1 = GeomVert((currVert.GetCo(0) + otherEdge1.GetCo(0))/2,(currVert.GetCo(1) + otherEdge1.GetCo(1))/2,(currVert.GetCo(2) + otherEdge1.GetCo(2))/2);
            GeomVert midE2 = GeomVert((currVert.GetCo(0) + otherEdge2.GetCo(0))/2,(currVert.GetCo(1) + otherEdge2.GetCo(1))/2,(currVert.GetCo(2) + otherEdge2.GetCo(2))/2);
            double vFx = (midE1.GetCo(0) + midE2.GetCo(0) + centroid.GetCo(0) + currVert.GetCo(0)) / 4.0;
            double vFy = (midE1.GetCo(1) + midE2.GetCo(1) + centroid.GetCo(1) + currVert.GetCo(1)) / 4.0;
            double vFz = (midE1.GetCo(2) + midE2.GetCo(2) + centroid.GetCo(2) + currVert.GetCo(2)) / 4.0;
            GeomVert currVf = GeomVert(vFx,vFy,vFz);
            vf.push_back(currVf);
            oriVert->addVertex(currFace.GetVertexInd(j), currVf);
            oriFace->addVertex(i,currVf);
            //oriVert->addFaceVertex(i, currVf);
        }
        meshOut->AddFacet(vf);

    }
}

GeomVert Subdivision::getCentroid(TopoFacet currface, Mesh* meshIn)
{
    double vX = 0;
    double vY = 0;
    double vZ = 0;
    int vertNum = currface.GetNumberVertices();
    for (int i = 0; i < vertNum; i++)
    {
        GeomVert v1 = meshIn->GetGeomVertex(currface.GetVertexInd(i));
        vX = vX + v1.GetCo(0)/vertNum;
        vY = vY + v1.GetCo(1)/vertNum;
        vZ = vZ + v1.GetCo(2)/vertNum;
    }
    GeomVert retVal = GeomVert(vX,vY,vZ);
    return retVal;
}

void Subdivision::dooSabinCalcEdge(Mesh *meshIn, Mesh *meshOut, OriginalVert *oriVert)
{
    for(int i = 0; i < meshIn->GetNumberEdges(); i++)
    {
        TopoEdge currEdge = meshIn->GetEdge(i);
        if (currEdge.GetNumberIncFacets() != 2){
            continue;
        }
        int f1 = currEdge.GetIncFacet(0);
        int f2 = currEdge.GetIncFacet(1);
        int v1 = currEdge.GetVertex(0);
        int v2 = currEdge.GetVertex(1);
        vector<GeomVert> v1Children = oriVert->getVertexList(v1);
        vector<GeomVert> v2Children = oriVert->getVertexList(v2);
        TopoFacet nF1 = meshOut->GetFacet(f1);
        TopoFacet nF2 = meshOut->GetFacet(f2);
        vector<GeomVert> vf;
        for(int j = 0; j < v1Children.size(); j++){
            GeomVert currV1 = v1Children.at(j);
            for(int k = 0; k < nF1.GetNumberVertices(); k++){
                GeomVert vOfFace = meshOut->GetGeomVertex(nF1.GetVertexInd(k));
                if (currV1 == vOfFace)
                    vf.push_back(currV1);
            }
            for(int k = 0; k < nF2.GetNumberVertices(); k++){
                GeomVert vOfFace = meshOut->GetGeomVertex(nF2.GetVertexInd(k));
                if (currV1 == vOfFace)
                    vf.push_back(currV1);
            }
        }
        for(int j = 0; j < v2Children.size(); j++){
            GeomVert currV2 = v2Children.at(j);
            for(int k = 0; k < nF1.GetNumberVertices(); k++){
                GeomVert vOfFace = meshOut->GetGeomVertex(nF1.GetVertexInd(k));
                if (currV2 == vOfFace)
                    vf.push_back(currV2);
            }
            for(int k = 0; k < nF2.GetNumberVertices(); k++){
                GeomVert vOfFace = meshOut->GetGeomVertex(nF2.GetVertexInd(k));
                if (currV2 == vOfFace)
                    vf.push_back(currV2);
            }
        }
        vector<GeomVert> add1;
        add1.push_back(vf.at(0));
        add1.push_back(vf.at(1));
        add1.push_back(vf.at(2));
        meshOut->AddFacet(add1);
        add1.clear();
        add1.push_back(vf.at(2));
        add1.push_back(vf.at(1));
        add1.push_back(vf.at(3));
        meshOut->AddFacet(add1);
    }
}

void Subdivision::dooSabinCalcVert(Mesh *meshIn, Mesh *meshOut, OriginalVert *oriVert, OriginalFace *oriFace)
{
    for(int i = 0; i < meshIn->GetNumberVertices(); i++){
        TopoVert currV = meshIn->GetVertex(i);
        if(currV.GetNumberIncFacets() < 3){
            continue;
        }
        vector<GeomVert> currList = oriVert->getVertexList(i);
        GeomVert startV = currList.at(0);
        TopoFacet startF;
        int startFidx;
        for(int j = 0; j < currV.GetNumberIncFacets(); j++){
            if (oriFace->checkVertex(currV.GetIncFacet(j),startV)){
                startFidx = currV.GetIncFacet(j);
                startF = meshIn->GetFacet(startFidx);
                break;
            }
        }
        vector<GeomVert> l1;
        l1.push_back(startV);

        vector<int> prevFidxes;
        prevFidxes.push_back(startFidx);
        int sample = 0;
        int nextFidx = startF.GetIncFacet(sample);
        while(!oriFace->checkCommon(nextFidx, currV, prevFidxes)){
            sample++;
            nextFidx = startF.GetIncFacet(sample);
        }
        prevFidxes.push_back(nextFidx);
        TopoFacet prevF = meshIn->GetFacet(nextFidx);
        vector<GeomVert> dummy = oriFace->getVList(nextFidx);
        GeomVert nextV = oriFace->checkMember(oriFace->getVList(nextFidx),currList);
        l1.push_back(nextV);
        bool stuck = false;
        int ongoing = 0;
        for(int j = 2; j < currList.size(); j ++){
            sample = 0;
            nextFidx = prevF.GetIncFacet(sample);
            while(!oriFace->checkCommon(nextFidx, currV, prevFidxes) && !stuck){
                sample++;
                if (sample > 10)
                    stuck = true;
                nextFidx = prevF.GetIncFacet(sample);
            }
            if(stuck){
                break;
                ongoing = j;
            }
            prevFidxes.push_back(nextFidx);
            prevF = meshIn->GetFacet(nextFidx);
            nextV = oriFace->checkMember(oriFace->getVList(nextFidx),currList);
            l1.push_back(nextV);
        }
        //START FROM OTHER SIDE OF START FACE
        if(stuck){
            sample = 0;
            nextFidx = 0;
            while(!oriFace->checkCommon(nextFidx, currV, prevFidxes)){
                sample++;
                nextFidx = startF.GetIncFacet(sample);
            }
            prevFidxes.push_back(nextFidx);
            prevF = meshIn->GetFacet(nextFidx);
            nextV = oriFace->checkMember(oriFace->getVList(nextFidx),currList);
            l1.push_back(nextV);

            for(int j = ongoing; j < currList.size(); j ++){
                sample = 0;
                nextFidx = prevF.GetIncFacet(sample);
                while(!oriFace->checkCommon(nextFidx, currV, prevFidxes) && !stuck){
                    sample++;
                    if (sample > 10)
                        stuck = true;
                    nextFidx = prevF.GetIncFacet(sample);
                }
                if(stuck){
                    break;
                }
                prevFidxes.push_back(nextFidx);
                prevF = meshIn->GetFacet(nextFidx);
                nextV = oriFace->checkMember(oriFace->getVList(nextFidx),currList);
                l1.push_back(nextV);
            }
        }

        meshOut->AddFacet(l1);
    }
}
