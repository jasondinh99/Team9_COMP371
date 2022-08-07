#pragma once
#include <iostream>
#include <list>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context, initializing OpenGL and binding inputs
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/gtc/type_ptr.hpp>
#include <glm/common.hpp>

#include <stdlib.h>

using namespace glm;
using namespace std;

class Cube
{
public:
	Cube(vec3, vec3);
	~Cube();
	float maxX = 0.5, minX = -0.5, maxY = 0.5, minY = -0.5, maxZ = 0.5, minZ = -0.5;
	inline vec3 GetPosition() { return centerPosition; }
	inline float GetMaxX() { return maxX; }
	inline float GetMinX() { return minX; }
	inline float GetMaxY() { return maxY; }
	inline float GetMinY() { return minY; }
	inline float GetMaxZ() { return maxZ; }
	inline float GetMinZ() { return minZ; }
private:
	vec3 centerPosition;
};