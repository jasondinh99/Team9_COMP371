#include <iostream>


#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices

#include <glm/common.hpp>
#include <vector>

# include "PerlinNoise.h"	// https://github.com/sol-prog/Perlin_Noise
#include <time.h>

#include "Shader.h"
#include "VAO.h"
#include "Model.h"
#include "Camera.h"
#include "Cube.h"

using namespace glm;
using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>

void handleInput(GLFWwindow* window, Camera* camera, float dt, float dx, float dy);
void terrainCollision(Camera* camera);

int currentCamera = 1;
Cube* physicalCubeArray[100];
int cubeNum = 0;
vec3 color = vec3(1.0f, 1.0f, 1.0f);

vec3 cubeArray[] = {  // position
         vec3(-0.5f,-0.5f,-0.5f), color, //left
         vec3(-0.5f,-0.5f, 0.5f), color,
         vec3(-0.5f, 0.5f, 0.5f), color,

         vec3(-0.5f,-0.5f,-0.5f), color,
         vec3(-0.5f, 0.5f, 0.5f), color,
         vec3(-0.5f, 0.5f,-0.5f), color,

         vec3(0.5f, 0.5f,-0.5f), color, // far
         vec3(-0.5f,-0.5f,-0.5f), color,
         vec3(-0.5f, 0.5f,-0.5f), color,

         vec3(0.5f, 0.5f,-0.5f), color,
         vec3(0.5f,-0.5f,-0.5f), color,
         vec3(-0.5f,-0.5f,-0.5f), color,

         vec3(0.5f,-0.5f, 0.5f), color, // bottom
         vec3(-0.5f,-0.5f,-0.5f), color,
         vec3(0.5f,-0.5f,-0.5f), color,

         vec3(0.5f,-0.5f, 0.5f), color,
         vec3(-0.5f,-0.5f, 0.5f), color,
         vec3(-0.5f,-0.5f,-0.5f), color,

         vec3(-0.5f, 0.5f, 0.5f), color, // near
         vec3(-0.5f,-0.5f, 0.5f), color,
         vec3(0.5f,-0.5f, 0.5f), color,

         vec3(0.5f, 0.5f, 0.5f), color,
         vec3(-0.5f, 0.5f, 0.5f), color,
         vec3(0.5f,-0.5f, 0.5f), color,

         vec3(0.5f, 0.5f, 0.5f), color, // right
         vec3(0.5f,-0.5f,-0.5f), color,
         vec3(0.5f, 0.5f,-0.5f), color,

         vec3(0.5f,-0.5f,-0.5f), color,
         vec3(0.5f, 0.5f, 0.5f), color,
         vec3(0.5f,-0.5f, 0.5f), color,

         vec3(0.5f, 0.5f, 0.5f), color, // top
         vec3(0.5f, 0.5f,-0.5f), color,
         vec3(-0.5f, 0.5f,-0.5f), color,

         vec3(0.5f, 0.5f, 0.5f), color,
         vec3(-0.5f, 0.5f,-0.5f), color,
         vec3(-0.5f, 0.5f, 0.5f), color
};



// To set different colors of letters
void setCubeColor(vec3 color)
{
    for (int i = 1; i < 72; i += 2)
    {
        cubeArray[i] = color;
    }
}

void setProjectionMatrix(int shaderProgram, mat4 projectionMatrix)
{
    glUseProgram(shaderProgram);
    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void setViewMatrix(int shaderProgram, mat4 viewMatrix)
{
    glUseProgram(shaderProgram);
    GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void setWorldMatrix(int shaderProgram, mat4 worldMatrix)
{
    glUseProgram(shaderProgram);
    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
}


Model model = Model();

int random(int min, int max) //range : [min, max]
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

int main(int argc, char* argv[])
{
    // Initialize GLFW and OpenGL version
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create Window and rendering context using GLFW, resolution is 1024*768
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Comp371 - Project", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Disable Mouse Cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Load Textures
    GLuint brickTextureID = model.loadTexture("assets/textures/brick.jpg");
    GLuint cementTextureID = model.loadTexture("assets/textures/cement.jpg");
    GLuint tree_barkTextureID = model.loadTexture("assets/textures/tree-bark.jpg");
    GLuint leavesTextureID = model.loadTexture("assets/textures/minecraft-leaves.png");

    // Grey background
    glClearColor(0.52f, 0.8f, 0.9f, 1.0f);

    // Compile and link shaders here ...
    Shader colorShaderProgram("SolidColor.vs", "SolidColor.fs");
    Shader texturedShaderProgram("Texture.vs", "Texture.fs");

    //glUseProgram(shaderProgram);
    colorShaderProgram.Activate();

    Camera* camera = nullptr;
    Camera* firstPersonCamera = new Camera(vec3(0.0f, 10.0f, 20.0f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f));
    Camera* staticCamera1 = new Camera(vec3(50.0f, 30.0f, 50.0f), vec3(-1.0f, -1.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f));
    Camera* staticCamera2 = new Camera(vec3(-50.0f, 30.0f, -50.0f), vec3(1.0f, -1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f));
    camera = firstPersonCamera;
    firstPersonCamera->EnableGravity();

    // Olaf parameters
    float posX = 0.0f;
    float posY = 0.0f;
    float posZ = 0.0f;

    float olafDeg = 0.0;
    float scaleXYZ = 1.0f;

    GLenum rendering = GL_TRIANGLES;


    // Set View and Projection matrices on both shaders
    setViewMatrix(colorShaderProgram.ID, camera->GetViewMatrix());
    setViewMatrix(texturedShaderProgram.ID, camera->GetViewMatrix());

    setProjectionMatrix(colorShaderProgram.ID, camera->GetProjectionMatrix());
    setProjectionMatrix(texturedShaderProgram.ID, camera->GetProjectionMatrix());



    // Define and upload geometry to the GPU here ...
    
    int gridAO = model.createGridAO();
    int terrainAO = model.createTerrainAO();
    int texturedCubeAO = model.createTexturedCubeAO();


    // For frame time
    float lastFrameTime = glfwGetTime();
    int lastMouseLeftState = GLFW_RELEASE;
    double lastMousePosX, lastMousePosY;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);


    // Enable Backface culling
    glEnable(GL_CULL_FACE);

    // Enable Depth Test
    glEnable(GL_DEPTH_TEST);

    cout << glGetString(GL_VERSION);

    //random variables
    srand(static_cast <unsigned> (time(0)));
    float randArray[5*2];
    for (int i = 0; i < 10; i++) {
        float rand1 = -50 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (50 - (-50))));
        randArray[i] = rand1;
    }

    // Entering Main Loop
    while (!glfwWindowShouldClose(window))
    {
        // Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // Each frame, reset color of each pixel to glClearColor
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLuint worldMatrixLocation = glGetUniformLocation(colorShaderProgram.ID, "worldMatrix");

        for (int i = 0; i < 100; i++)
            physicalCubeArray[i] = nullptr;
        cubeNum = 0;
        
        // Draw 100x100 Grid
        glUseProgram(colorShaderProgram.ID);
        glBindVertexArray(terrainAO);
        glDrawElements(GL_TRIANGLE_STRIP, 99 * 99 * 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(gridAO);
        mat4 gridWorldMatrix;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                gridWorldMatrix = translate(mat4(1.0f), vec3(-50.0f + i, 0.0f, -50.0f + j)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
                setWorldMatrix(colorShaderProgram.ID, gridWorldMatrix);
                glDrawArrays(GL_LINE_LOOP, 0, 4);

            }
        }

        /*Draw Tree*/
        glBindVertexArray(texturedCubeAO);

        // Draw Textured geometry
        glUseProgram(texturedShaderProgram.ID);
       


        for (int i = 0; i < 10; i += 2) {

            glActiveTexture(GL_TEXTURE0);
        GLuint textureLocation = glGetUniformLocation(texturedShaderProgram.ID, "textureSampler");
        glBindTexture(GL_TEXTURE_2D, tree_barkTextureID);
        glUniform1i(textureLocation, 0);

            float trunkX = 0.0f + randArray[i];
            float trunkY = 10.0f;
            float trunkZ = 0.0f + randArray[i + 1];

            mat4 treeWorldMatrix = translate(mat4(1.0f), vec3(trunkX , trunkY, trunkZ)) * scale(mat4(1.0f), vec3(2.0f, 20.0f, 2.0f));
            setWorldMatrix(texturedShaderProgram.ID, treeWorldMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            physicalCubeArray[cubeNum++] = new Cube(vec3(trunkX , trunkY, trunkZ), vec3(2.0f, 20.0f, 2.0f));

            glBindTexture(GL_TEXTURE_2D, leavesTextureID);
            for (int j = 0; j < 12; j += 2)
            {
                treeWorldMatrix = translate(mat4(1.0f), vec3(trunkX , trunkY + j, trunkZ)) * scale(mat4(1.0f), vec3(15.0f - j, 1.0f, 3.0f));
                setWorldMatrix(texturedShaderProgram.ID, treeWorldMatrix);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                physicalCubeArray[cubeNum++] = new Cube(vec3(trunkX , trunkY + j, trunkZ), vec3(15.0f - j, 1.0f, 3.0f));

                treeWorldMatrix = translate(mat4(1.0f), vec3(trunkX , trunkY + j, trunkZ)) * scale(mat4(1.0f), vec3(3.0f, 1.0f, 15.0f - j));
                setWorldMatrix(texturedShaderProgram.ID, treeWorldMatrix);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                physicalCubeArray[cubeNum++] = new Cube(vec3(trunkX , trunkY + j, trunkZ), vec3(3.0f, 1.0f, 15.0f - j));
            }
        }

        /*Draw Apple Tree*/
        glBindVertexArray(texturedCubeAO);

        // Draw Textured geometry
        glUseProgram(texturedShaderProgram.ID);

        glActiveTexture(GL_TEXTURE0);
        GLuint textureLocation = glGetUniformLocation(texturedShaderProgram.ID, "textureSampler");
        glBindTexture(GL_TEXTURE_2D, tree_barkTextureID);
        glUniform1i(textureLocation, 0);

        float trunkX = 0.0f;
        float trunkY = 10.0f;
        float trunkZ = 0.0f;

        mat4 treeWorldMatrix = translate(mat4(1.0f), vec3(trunkX, trunkY, trunkZ)) * scale(mat4(1.0f), vec3(2.0f, 20.0f, 2.0f));
        setWorldMatrix(texturedShaderProgram.ID, treeWorldMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw Branches Bottom
        glBindTexture(GL_TEXTURE_2D, leavesTextureID);
       for (int y = 0; y < 5; y++)
        {
            for (int x = -1-y; x < 2+y; x++)
            {
                for (int z = -1-y; z < 2+y; z++)
                {
                    treeWorldMatrix = translate(mat4(1.0f), vec3(trunkX + x, trunkY + y, trunkZ + z)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
                    setWorldMatrix(texturedShaderProgram.ID, treeWorldMatrix);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }

       // Draw Branches Top

        for (int y = 0; y < 5; y++)
        {
            for (int x = -5 + y; x < 7 - y; x++)
            {
                for (int z = -5 + y; z < 7 - y; z++)
                {
                    treeWorldMatrix = translate(mat4(1.0f), vec3(trunkX + x, trunkY + (y+5), trunkZ + z)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
                    setWorldMatrix(texturedShaderProgram.ID, treeWorldMatrix);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }
       

       


        glBindVertexArray(0);
        // End Frame

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Handle inputs
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        //  re-position the Olaf at a random location on the grid
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            posX = (rand() % 99) - 49;
            posZ = (rand() % 99) - 49;
        }

        //Shift
        bool shiftPressed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;


        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        double dx = mousePosX - lastMousePosX;
        double dy = mousePosY - lastMousePosY;

        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

        if (currentCamera == 1)
            camera = firstPersonCamera;
        else if (currentCamera == 2)
            camera = staticCamera1;
        else
            camera = staticCamera2;

        camera->Update(&model, dt);

        //terrainCollision(camera);
        handleInput(window, firstPersonCamera, dt, dx, dy);


        //// Convert to spherical coordinates
        //const float cameraAngularSpeed = 1.0f;
        //
        //cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
        //cameraVerticalAngle -= dy * cameraAngularSpeed * dt;



        //// World Orientation
        // // Clamp vertical angle to [-85, 85] degrees
        //cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
        //if (cameraHorizontalAngle > 360)
        //{
        //    cameraHorizontalAngle -= 360;
        //}
        //else if (cameraHorizontalAngle < -360)
        //{
        //    cameraHorizontalAngle += 360;
        //}

        //float theta = radians(cameraHorizontalAngle);
        //float phi = radians(cameraVerticalAngle);
        //
        //cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
        //vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));
        //
        //glm::normalize(cameraSideVector);

        setViewMatrix(colorShaderProgram.ID, camera->GetViewMatrix());
        setViewMatrix(texturedShaderProgram.ID, camera->GetViewMatrix());

        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        {
            camera->SetPosition(vec3(5.0f, 1.0f, 50.0f));

            setViewMatrix(colorShaderProgram.ID, camera->GetViewMatrix());
            setViewMatrix(texturedShaderProgram.ID, camera->GetViewMatrix());
        }

    }

    // Shutdown GLFW
    glfwTerminate();

    return 0;
}

void handleInput(GLFWwindow* window, Camera* camera, float dt, float dx, float dy)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)      // close screen
        glfwSetWindowShouldClose(window, true);

    // Choose camera
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)      // close screen
        currentCamera = 1;

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)      // close screen
        currentCamera = 2;

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)      // close screen
        currentCamera = 3;

    // WASD
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // move camera forward
        camera->Move(true, dt);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // move camera backward
        camera->Move(true, -dt);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // move camera to the left
        camera->Move(false, -dt);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // move camera to the right
		camera->Move(false, dt);


    // zoom
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) // zoom out
        camera->Move(true, dt);

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) //Zoom in
        camera->Move(true, -dt);

    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) //Zoom in
        camera->EnableGravity();

    if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS) //Zoom in
        camera->DisableGravity();

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) //Zoom in
        camera->Jump();

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) //Zoom in
        camera->FastSpeed();

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) //Zoom in
        camera->NormalSpeed();

    // Mouse buttons
    camera->Turn(dx * -0.01, dy * -0.01);
}