#include "meshreader.h"

Mesh MeshReader::readMesh(string input)
{
    Mesh retVal;
    string line;
    ifstream meshFile(input);
    if(meshFile.is_open()){
        getline(meshFile,line); // take OFF
        getline(meshFile,line); // get vert#, face#
        int VFSeparator = line.find(" ");
        string vertexNum = line.substr(0,VFSeparator);
        string faceNum = line.substr(VFSeparator + 1,line.find(" ",VFSeparator + 1) - VFSeparator - 1);
        int vNum = stoi(vertexNum,nullptr,10);
        int fNum = stoi(faceNum,nullptr,10);
        CatmullOriginal vOri = CatmullOriginal();
        for(int i = 0; i < vNum; i++){
            getline(meshFile,line);
            int XYsep = line.find(" ");
            int YZsep = line.find(" ", XYsep + 1);
            double x = stod(line.substr(0,XYsep));
            double y = stod(line.substr(XYsep + 1, YZsep - XYsep - 1));
            double z = stod(line.substr(YZsep));
            GeomVert add = GeomVert(x,y,z);
            vOri.addVertex(i,add);
        }
        for(int i = 0; i < fNum; i++){
            getline(meshFile,line);
            int FVsep = line.find(" ");
            int Vsep = line.find(" ", FVsep + 2);
            int prevVsep = FVsep;
            int faceVertNum = stoi(line.substr(0,FVsep));
            vector<GeomVert> faceAdd;
            for(int j = 0; j < faceVertNum; j++){
                string dummy = line.substr(prevVsep + 1, Vsep -prevVsep - 1);
                int vert = stoi(line.substr(prevVsep + 1, Vsep -prevVsep - 1));
                prevVsep = Vsep;
                Vsep = line.find(" ", Vsep + 1);
                faceAdd.push_back(vOri.getNewVertex(vert));
            }
            retVal.AddFacet(faceAdd);
            faceAdd.clear();
        }
    } else {
        cout << "unable to open file";
    }

    return retVal;
}
