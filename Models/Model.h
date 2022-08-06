#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices

#include <glm/common.hpp>

#include "VAO.h"
#include "PerlinNoise.h"


using namespace glm;
using namespace std;


class Model
{
public:

	// Variables
	VAO vao;

	// Constructors
	Model();

	// Methods
	int createGridAO();
	int createTexturedCubeAO();
	int createTerrainAO();
	GLuint loadTexture(const char* filename);

private:
	
};




#endif