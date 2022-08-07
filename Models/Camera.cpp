#include "Camera.h"

Camera::Camera(vec3 position, vec3 lookAt, vec3 upVector)
    : cameraPosition(position), cameraLookAt(lookAt), cameraUp(upVector), cameraSpeed(1.0f), cameraNormalSpeed(1.0f), cameraFastSpeed(2.0f), cameraAngularSpeed(60.0f), cameraHorizontalAngle(90.0f), cameraVerticalAngle(0.0f), withGravity(false) {}

mat4 Camera::GetViewProjectionMatrix() const
{

    mat4 viewProjection(1.0f);

    // Solution
#if 1
    viewProjection = GetProjectionMatrix() * GetViewMatrix();
#endif

    return viewProjection;
}

mat4 Camera::GetProjectionMatrix() const
{
    return perspective(70.0f, 1024.0f / 768.0f, 0.01f, 100.0f);   // near and far (near > 0)
        //perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    
}

mat4 Camera::GetViewMatrix() const
{
    return lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp);
    //viewMatrix = lookAt(cameraPosition,  // eye
    //    cameraPosition + cameraLookAt,  // center
    //    cameraUp); // up
}


void Camera::setProjectionMatrix(int shaderProgram, mat4 projectionMatrix)
{
    glUseProgram(shaderProgram);
    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Camera::setViewMatrix(int shaderProgram, mat4 viewMatrix)
{
    glUseProgram(shaderProgram);
    GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}


void Camera::Update(Model* model, vector<Cube> cubes, float dt)
{
    // Apply gravity
    if (withGravity)
        cameraPosition += vec3(0.0f, -1.0f, 0.0f) * dt * gravity;

    CheckCollision(cubes);
    CheckBoundary();
    TerrainCollision(model);

    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &GetViewMatrix()[0][0]);
}

void Camera::Turn(float dx, float dy)
{
    cameraHorizontalAngle += cameraAngularSpeed * dx;
    cameraVerticalAngle += cameraAngularSpeed * dy;

    // Clamp vertical angle to [-85, 85] degrees
    cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
    if (cameraHorizontalAngle > 360)
    {
        cameraHorizontalAngle -= 360;
    }
    else if (cameraHorizontalAngle < -360)
    {
        cameraHorizontalAngle += 360;
    }

    float theta = radians(cameraHorizontalAngle);
    float phi = radians(cameraVerticalAngle);

    cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));

    vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

    glm::normalize(cameraSideVector);
}

void Camera::Move(bool option, float dt)
{
    float normalizedSpeed = cameraSpeed * 5 * dt;

    vec3 cameraSideVector = glm::cross(cameraLookAt, cameraUp);
    glm::normalize(cameraSideVector);

    if(option == true)
        cameraPosition += cameraLookAt * normalizedSpeed;
    else
        cameraPosition += cameraSideVector * normalizedSpeed;

    CheckBoundary();
}

void Camera::Reset()
{
    cameraPosition = vec3(0.0f, 4.0f, 30.0f);
    cameraLookAt = vec3(0.0f, 0.0f, -1.0f);
    cameraUp = vec3(0.0f, 1.0f, 0.0f);
}

void Camera::EnableGravity()
{
    withGravity = true;
}

void Camera::DisableGravity()
{
    withGravity = false;
}

void Camera::Jump()
{
    cameraPosition += vec3(0.0f, 2.0f, 0.0f);
}

void Camera::FastSpeed()
{
    cameraSpeed = cameraFastSpeed;
}

void Camera::NormalSpeed()
{
    cameraSpeed = cameraNormalSpeed;
}

bool Camera::CheckCollision(vector<Cube> cubes)
{
    bool collisionX = false;
    bool collisionY = false;
    bool collisionZ = false;
    float xDif = 1000.0;
    float yDif = 1000.0;
    float zDif = 1000.0;
    float xStop = 0.0;
    float yStop = 0.0;
    float zStop = 0.0;

    for (Cube cube : cubes)
    {
        collisionX = cameraPosition.x >= cube.GetMinX() - 0.1 && cameraPosition.x <= cube.GetMaxX()+0.1;
        collisionY = cameraPosition.y >= cube.GetMinY() - 0.1 && cameraPosition.y <= cube.GetMaxY()+0.1;
        collisionZ = cameraPosition.z >= cube.GetMinZ() - 0.1 && cameraPosition.z <= cube.GetMaxZ()+0.1;
        
        if ((collisionX && collisionY) && (collisionX && collisionZ))
        {
            if (collisionX)
            {
                if (cameraPosition.x - cube.GetMinX() > cube.GetMaxX() - cameraPosition.x)
                {
                    xDif = cube.GetMaxX() - cameraPosition.x;
                    xStop = cube.GetMaxX() + 0.1;
                }
                else
                {
                    xDif = cameraPosition.x - cube.GetMinX();
                    xStop = cube.GetMinX() - 0.1;
                }
            }
            if (collisionY)
            {
                if (cameraPosition.y - cube.GetMinY() > cube.GetMaxY() - cameraPosition.y)
                {
                    yDif = cube.GetMaxY() - cameraPosition.y;
                    yStop = cube.GetMaxY() + 0.1;
                }
                else
                {
                    yDif = cameraPosition.y - cube.GetMinY();
                    yStop = cube.GetMinY() - 0.1;
                }
            }
            if (collisionZ)
            {
                if (cameraPosition.z - cube.GetMinZ() > cube.GetMaxZ() - cameraPosition.z)
                {
                    zDif = cube.GetMaxZ() - cameraPosition.z;
                    zStop = cube.GetMaxZ() + 0.1;
                }
                else
                {
                    zDif = cameraPosition.z - cube.GetMinZ();
                    zStop = cube.GetMinZ() - 0.1;
                }
            }

            if (xDif < yDif && xDif < zDif)
                cameraPosition.x = xStop;
            if (yDif < xDif && yDif < zDif)
                cameraPosition.y = yStop;
            if (zDif < yDif && zDif < xDif)
                cameraPosition.z = zStop;

            //cout << "INTERSECTION DETECTED at" << xDif << " " << yDif << " " << zDif << endl;

            return true;
        }

    }
    return false;
}

void Camera::CheckBoundary()
{
    // To make sure that cameras do not go out of the field
    if (cameraPosition.x > 50)
        cameraPosition.x = -50;
    else if (cameraPosition.x < -50)
        cameraPosition.x = 50;

    if (cameraPosition.y > 50)
        cameraPosition.y = 50;
    else if (cameraPosition.y < 1.1)
        cameraPosition.y = 1.1;

    if (cameraPosition.z > 50)
        cameraPosition.z = -50;
    else if (cameraPosition.z < -50)
        cameraPosition.z = 50;
}

void Camera::TerrainCollision(Model* model)
{
    float xCoordinate = -cameraPosition.x + 49.0;
    float zCoordinate = -cameraPosition.z + 50.0;
    if (cameraPosition.y <= model->getTerrainHeightAt(xCoordinate, zCoordinate) + 1.1)
    {
        cameraPosition.y = model->getTerrainHeightAt(xCoordinate, zCoordinate) + 1.1;
    }
}