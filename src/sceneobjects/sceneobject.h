#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shaders/program.h"
#include "../assets/texture.h"
#include "../light/lightsinfo.h"
#include "../assets/material.h"
#include "../assets/model.h"

class SceneObject
{

public:

    SceneObject();
    ~SceneObject();

    // const std::vector<Program> getProgrammes();
    // const std::vector<Texture> getTextures();

    void addProgram(Program program);
    // void addTextures(Texture texture);
    void applyModel(Model& model);

    void requireModel(std::string modelName);
    bool hasModelRequired();
    const std::string getModelName();
    /**
     * Matrix model position of current SceneObject
     */
    glm::mat4 matrixModel(const glm::vec3 cameraPosition);

    void render(const glm::mat4 matrixProjection, const glm::mat4 matrixView, const glm::vec3 cameraPosition);

    // bool test = false;

    std::vector<Program> programmes;
    // std::vector<Texture> textures;

    LightsInfo lights;
    Material material;
    // Data data;
    glm::vec3 position = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

    bool simpleAnimation = false;
private:

    float tmp = 0.1f;
    // std::string modelPath = "";
    std::string modelName = "";

    void debugProgram(Program program);

};

#endif // SCENEOBJECT_H
