#include "scene.h"
#include "logger.h"

Scene::Scene()
{
    cameraPosition = glm::vec3(0.5f, 0.5f, 0.5f);
}

Scene::~Scene()
{

}


/* Геттеры */

//  std::vector<SceneObject> Scene::getSceneObjects()
// {
//     return this->sceneObjects;
// }


/* Действия */

void Scene::addSceneObject(SceneObject sceneObject)
{
    // this->sceneObjects.insert(this->sceneObjects.begin(), sceneObject);
    this->sceneObjects.push_back(sceneObject);
}

// void Scene::removeSceneObject(int index)
// {
//
// }


/* Матрицы */
const glm::mat4 Scene::matrixProjection(float fov)
{
    return glm::perspective(
        glm::radians(fov), 	// угол обзора в радианах обычно берётся в диапазоне 30-120 градусов
        (float)640 / 480,       // соотношение сторон экрана
        0.01f,              // расстояние от наблюдателя до ближней плоскости отсечения
        100.0f             //расстояние от наблюдателя до дальней плоскости отсечения
    );
}

const glm::mat4 Scene::matrixView()
{
    return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}




/* Render */

void Scene::render(float fov)
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    // cameraPosition = glm::vec3(tmp, tmp, 0.5f);
    // tmp += 0.01f;

    for(SceneObject& obj : sceneObjects) {
        obj.render(matrixProjection(fov), matrixView(), cameraPosition);
    }


    // Отрисовываем CubeMap
    cubeMap.render(matrixProjection(fov), matrixView(), cameraPosition);
}


