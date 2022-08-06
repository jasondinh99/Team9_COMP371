#include "cube.h"

Cube::Cube(vec3 translation, vec3 scalee)
//    : color(color), shaderID(shaderID), textureID(textureID), hierarchicalMatrix(mat4(1.0f)), worldMatrix(mat4(1.0f)), movementMatrix(mat4(1.0f)), animationMatrix(mat4(1.0f))
{
//    originalMatrix = cubeMatrix = translate(mat4(1.0f), translation) * scale(mat4(1.0f), scalee);
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

//    shapeWorldMatrixLocation = glGetUniformLocation(shaderID, "worldMatrix");
//
//    createTexturedCubeVertexArrayObject();
//    glGenBuffers(1, &primitiveBuffer);
}

//Cube::Cube(mat4 shapeWorldMatrix, vec3 color, GLuint textureID, int shaderID)
//    : cubeMatrix(shapeWorldMatrix), color(color), shaderID(shaderID), textureID(textureID),
//    originalMatrix(cubeMatrix), hierarchicalMatrix(mat4(1.0f)), worldMatrix(mat4(1.0f)), movementMatrix(mat4(1.0f)), animationMatrix(mat4(1.0f))
//{
//    shapeWorldMatrixLocation = glGetUniformLocation(shaderID, "worldMatrix");
//
//    createTexturedCubeVertexArrayObject();
//    glGenBuffers(1, &primitiveBuffer);
//}

Cube::~Cube() {}

//void Cube::Draw()
//{
//    //glUseProgram(shaderID);
//    //glBindVertexArray(vertexArrayObject);
//    //glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, primitiveBuffer);
//
//    ////bind texture
//    //glActiveTexture(GL_TEXTURE0);
//    //GLuint textureLocation = glGetUniformLocation(shaderID, "textureSampler");
//    //glBindTexture(GL_TEXTURE_2D, textureID);
//    //glUniform1i(textureLocation, 0);
//
//    //// setWorldMatrix
//    //mat4 drawMatrix = worldMatrix * hierarchicalMatrix * movementMatrix * animationMatrix * cubeMatrix;
//    //shapeWorldMatrixLocation = glGetUniformLocation(shaderID, "worldMatrix");
//    //glUniformMatrix4fv(shapeWorldMatrixLocation, 1, GL_FALSE, &drawMatrix[0][0]);
//
//    //if (renderMode == 0)
//    //    glDrawArrays(GL_TRIANGLES, 0, 36);
//    //else if (renderMode == 1)
//    //    glDrawArrays(GL_LINES, 0, 36);
//    //else if (renderMode == 2)
//    //    glDrawArrays(GL_POINTS, 0, 36);
//
//    glBindVertexArray(vertexArrayObject);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, primitiveBuffer);
//
//
//    mat4 drawMatrix = worldMatrix * hierarchicalMatrix * movementMatrix * animationMatrix * cubeMatrix;
//
//    shapeWorldMatrixLocation = glGetUniformLocation(shaderID, "worldMatrix");
//
//    glUniformMatrix4fv(shapeWorldMatrixLocation, 1, GL_FALSE, &drawMatrix[0][0]);
//
//    glUseProgram(shaderID);
//
//    glActiveTexture(GL_TEXTURE0 + textureID - 1);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    GLuint textureLocation = glGetUniformLocation(shaderID, "textureSampler");
//    glUniform1i(textureLocation, textureID - 1);
//
//    if (renderMode == 0)
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//    else if (renderMode == 1)
//        glDrawArrays(GL_LINES, 0, 36);
//    else if (renderMode == 2)
//        glDrawArrays(GL_POINTS, 0, 36);
//}
//
//void Cube::setRenderMode(int mode)
//{
//    renderMode = mode;
//}
//
//void Cube::Rotate(float angle, vec3 transformation)
//{
//    cubeMatrix *= rotate(mat4(1.0f), radians(angle), transformation);
//}
//
//void Cube::Translate(vec3 transformation)
//{
//    cubeMatrix *= translate(mat4(1.0f), transformation);
//}
//
//void Cube::Scale(vec3 transformation)
//{
//    cubeMatrix *= scale(mat4(1.0f), transformation);
//}
//
//void Cube::RotateHierarchical(float angle, vec3 transformation)
//{
//    hierarchicalMatrix *= rotate(mat4(1.0f), radians(angle), transformation);
//}
//
//void Cube::TranslateHierarchical(vec3 transformation)
//{
//    hierarchicalMatrix *= translate(mat4(1.0f), transformation);
//}
//
//void Cube::ScaleHierarchical(vec3 transformation)
//{
//    hierarchicalMatrix *= scale(mat4(1.0f), transformation);
//}
//
//void Cube::RotateAnimation(float angle, vec3 transformation)
//{
//    animationMatrix *= rotate(mat4(1.0f), radians(angle), transformation);
//}
//
//void Cube::TranslateAnimation(vec3 transformation)
//{
//    animationMatrix *= translate(mat4(1.0f), transformation);
//}
//
//void Cube::ScaleAnimation(vec3 transformation)
//{
//    animationMatrix *= scale(mat4(1.0f), transformation);
//}
//
//vec3 Cube::Random()
//{
//    hierarchicalMatrix = mat4(1.0f);
//    float x = ((float)rand() / (RAND_MAX) * 100.0) - 50.0;
//    float z = ((float)rand() / (RAND_MAX) * 100.0) - 50.0;
//
//    hierarchicalMatrix *= translate(mat4(1.0f), vec3(x, 0.0f, z));
//
//    return (vec3(x, 0.0f, z));
//}
//
//void Cube::RandomHierarchical(vec3 transformation)
//{
//
//    hierarchicalMatrix = mat4(1.0f);
//    hierarchicalMatrix *= translate(mat4(1.0f), transformation);
//}
//
//void Cube::Reset()
//{
//    cubeMatrix = originalMatrix;
//    hierarchicalMatrix = mat4(1.0f);
//    worldMatrix = mat4(1.0f);
//    movementMatrix = mat4(1.0f);
//    animationMatrix = mat4(1.0f);
//}
//
//void Cube::ResetAnimation()
//{
//    animationMatrix = mat4(1.0f);
//}
//
//void Cube::RotateWorld(float angle, vec3 transformation)
//{
//    worldMatrix *= rotate(mat4(1.0f), radians(angle), transformation);
//}
//
//int Cube::createTexturedCubeVertexArrayObject()
//{
//    // Textured Cube model
//    TexturedColoredVertex texturedCubeVertexArray[] = {  // position,                            color
//    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), this->color, vec2(0.0f, 0.0f)), //left
//    TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), this->color, vec2(0.0f, 1.0f)),
//    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), this->color, vec2(1.0f, 1.0f)),
//
//    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), this->color, vec2(0.0f, 0.0f)),
//    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), this->color, vec2(1.0f, 1.0f)),
//    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), this->color, vec2(1.0f, 0.0f)),
//
//    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), this->color,   vec2(1.0f, 1.0f)), // far
//    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), this->color, vec2(0.0f, 0.0f)),
//    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), this->color, vec2(0.0f, 1.0f)),
//
//    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), this->color, vec2(1.0f, 1.0f)),
//    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), this->color, vec2(1.0f, 0.0f)),
//    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), this->color, vec2(0.0f, 0.0f)),
//
//    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), this->color, vec2(1.0f, 1.0f)), // bottom
//    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), this->color, vec2(0.0f, 0.0f)),
//    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), this->color, vec2(1.0f, 0.0f)),
//
//    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), this->color, vec2(1.0f, 1.0f)),
//    TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), this->color, vec2(0.0f, 1.0f)),
//    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), this->color, vec2(0.0f, 0.0f)),
//
//    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), this->color, vec2(0.0f, 1.0f)), // near
//    TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), this->color, vec2(0.0f, 0.0f)),
//    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), this->color, vec2(1.0f, 0.0f)),
//
//    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), this->color, vec2(1.0f, 1.0f)),
//    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), this->color, vec2(0.0f, 1.0f)),
//    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), this->color, vec2(1.0f, 0.0f)),
//
//    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), this->color, vec2(1.0f, 1.0f)), // right
//    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), this->color, vec2(0.0f, 0.0f)),
//    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), this->color, vec2(1.0f, 0.0f)),
//
//    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), this->color, vec2(0.0f, 0.0f)),
//    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), this->color, vec2(1.0f, 1.0f)),
//    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), this->color, vec2(0.0f, 1.0f)),
//
//    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), this->color, vec2(1.0f, 1.0f)), // top
//    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), this->color, vec2(1.0f, 0.0f)),
//    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), this->color, vec2(0.0f, 0.0f)),
//
//    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), this->color, vec2(1.0f, 1.0f)),
//    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), this->color, vec2(0.0f, 0.0f)),
//    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), this->color, vec2(0.0f, 1.0f))
//    };
//
//    // Create a vertex array
//    glGenVertexArrays(1, &vertexArrayObject);
//    glBindVertexArray(vertexArrayObject);
//
//    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
//    glGenBuffers(1, &vertexBufferObject);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCubeVertexArray), texturedCubeVertexArray, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
//        3,                   // size
//        GL_FLOAT,            // type
//        GL_FALSE,            // normalized?
//        sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color)
//        (void*)0             // array buffer offset
//    );
//    glEnableVertexAttribArray(0);
//
//
//    glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
//        3,
//        GL_FLOAT,
//        GL_FALSE,
//        sizeof(TexturedColoredVertex),
//        (void*)sizeof(vec3)      // color is offseted a vec3 (comes after position)
//    );
//    glEnableVertexAttribArray(1);
//
//    glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
//        2,
//        GL_FLOAT,
//        GL_FALSE,
//        sizeof(TexturedColoredVertex),
//        (void*)(2 * sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
//    );
//    glEnableVertexAttribArray(2);
//
//    return vertexArrayObject;
//}
