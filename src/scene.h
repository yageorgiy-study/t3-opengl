#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "sceneobjects/sceneobject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "assets/cubemap.h"

class Scene
{

public:
    Scene();
    ~Scene();

     // std::vector<SceneObject> getSceneObjects();
    void addSceneObject(SceneObject sceneObject);
    // void removeSceneObject(int index);

    /**
     * Camera projection matrix (ortho or perspective)
     */
    const glm::mat4 matrixProjection(float fov);

    /**
     * Viewpoint matrix
     */
    const glm::mat4 matrixView();

    void render(float fov);

    CubeMap cubeMap;

    std::vector<SceneObject> sceneObjects;
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    float tmp = 0.3f;

private:
    int compiledShaders = 0;

};

#endif // SCENE_H

