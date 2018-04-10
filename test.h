#ifndef TEST_H
#define TEST_H

#include "mesh.h"
#include "subdivision.h"
#include "catmullclark.h"
#include "loopsubdiv.h"

class Test
{
public:
    static void test1DSB(Mesh* meshIn, Mesh* meshOut);
    static Mesh test1CCL(Mesh* meshIn);
    static Mesh test1LOOP(Mesh* meshIn);
    static void test2DSB(Mesh* meshIn, Mesh* meshOut);
    static void test3DSB(Mesh* meshIn, Mesh* meshOut);
    static void testVanish(Mesh* meshIn);
private:
};

#endif // TEST_H
