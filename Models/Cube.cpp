#include "cube.h"

Cube::Cube(vec3 translation, vec3 scalee)
{
    centerPosition = translation;
    
    maxX *= scalee.x;
    minX *= scalee.x;
    maxY *= scalee.y;
    minY *= scalee.y;
    maxZ *= scalee.z;
    minZ *= scalee.z;
    
    maxX += translation.x;
    minX += translation.x;
    maxY += translation.y;
    minY += translation.y;
    maxZ += translation.z;
    minZ += translation.z;
}

Cube::~Cube() {}