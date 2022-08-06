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


//const vec3 BLACK = vec3(0.0f, 0.0f, 0.0f);
//const vec3 WHITE = vec3(1.0f, 1.0f, 1.0f);
//const vec3 RED = vec3(1.0f, 0.0f, 0.0f);
//const vec3 GREEN = vec3(0.0f, 1.0f, 0.0f);
//const vec3 BLUE = vec3(0.0f, 0.0f, 1.0f);

class Cube
{
public:
	Cube(vec3, vec3);
//	Cube(mat4, vec3, GLuint, int);
	~Cube();
//	void Draw();
//	void Rotate(float, vec3);
//	void Translate(vec3);
//	void Scale(vec3);
//	vec3 Random();
//	void RotateHierarchical(float, vec3);
//	void TranslateHierarchical(vec3);
//	void ScaleHierarchical(vec3);
//	void RandomHierarchical(vec3);
//	void RotateWorld(float, vec3);
//	void Reset();
//	void setRenderMode(int);
//	void RotateAnimation(float, vec3);
//	void TranslateAnimation(vec3);
//	void ScaleAnimation(vec3);
//	void ResetAnimation();
	inline vec3 GetPosition() { return centerPosition; }
	inline float GetMaxX() { return maxX; }
	inline float GetMinX() { return minX; }
	inline float GetMaxY() { return maxY; }
	inline float GetMinY() { return minY; }
	inline float GetMaxZ() { return maxZ; }
	inline float GetMinZ() { return minZ; }
private:
//	int shaderID;
//	GLuint shapeWorldMatrixLocation;
//	GLuint textureID;
//	GLuint vertexArrayObject;
//	GLuint vertexBufferObject;
//	GLuint primitiveBuffer;
//	mat4 originalMatrix;		// original shape
//	mat4 cubeMatrix;			// transformation applied on the cube
//	mat4 hierarchicalMatrix;	// hierarchical
//	mat4 worldMatrix;			// for world orientation
//	mat4 movementMatrix;
//	mat4 animationMatrix;
	vec3 centerPosition;
//	vec3 color;
//	int renderMode = 0;			// 0: triangles;	1: lines;	2: points
//	float angle = 0.0f;
	float maxX = 0.5, minX = -0.5, maxY = 0.5, minY = -0.5, maxZ = 0.5, minZ = -0.5;

//	struct TexturedColoredVertex
//	{
//		TexturedColoredVertex(vec3 _position, vec3 _color, vec2 _uv)
//			: position(_position), color(_color), uv(_uv) {}
//
//		vec3 position;
//		vec3 color;
//		vec2 uv;
//	};
//
//	int createTexturedCubeVertexArrayObject();
};