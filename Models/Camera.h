#pragma once
#include <iostream>
#include <list>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

using namespace glm;
using namespace std;

class Camera
{
public:
    Camera(vec3, vec3, vec3);
    void Update(float);
    void Turn(float, float);
    void Move(bool, float);
    void Reset();
    mat4 GetViewProjectionMatrix() const;
    mat4 GetProjectionMatrix() const;
    mat4 GetViewMatrix() const;
    inline void setPosition(vec3 position) { cameraPosition = position; }
    void setViewMatrix(int, mat4);
    void setProjectionMatrix(int, mat4);
    void setShaderProgram(int);
    float cameraSpeed;
private:
    GLuint projectionMatrixLocation;
    GLuint viewMatrixLocation;

    vec3 cameraPosition;
    vec3 cameraLookAt;
    vec3 cameraUp;
    float cameraFastSpeed;
    float cameraHorizontalAngle;
    float cameraVerticalAngle;
    float cameraAngularSpeed;
    int type;
};