#ifndef MESHREADER_H
#define MESHREADER_H

#include "mesh.h"
#include <iostream>
#include <fstream>
#include "catmulloriginal.h"

class MeshReader
{
public:
    Mesh static readMesh(std::string input);
};
#endif // MESHREADER_H
