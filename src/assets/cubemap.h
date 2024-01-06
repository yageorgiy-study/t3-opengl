#ifndef CUBEMAPTEXTURE_H
#define CUBEMAPTEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "texture.h"
#include "texturestatus.h"
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shaders/program.h"

/**
 * @todo write docs
 */
class CubeMap
{
public:
    /**
     * Default constructor
     */
    CubeMap();

    /**
     * Destructor
     */
    ~CubeMap();

    void requireCubemapTextures(std::initializer_list<std::string> list);

    const Program getProgram();

    void importTextures();
    void load();

    void render(const glm::mat4 matrixProjection, const glm::mat4 matrixView, const glm::vec3 cameraPosition);


    const TextureStatus getTextureStatus();
    const CompileStatus getCompileStatus();

    std::vector<glm::vec3> vertices = {
        glm::vec3(-100.0f, -100.0f,  100.0f),
        glm::vec3(100.0f, -100.0f,  100.0f),
        glm::vec3(100.0f, -100.0f, -100.0f),
        glm::vec3(-100.0f, -100.0f, -100.0f),
        glm::vec3(-100.0f,  100.0f,  100.0f),
        glm::vec3(100.0f,  100.0f,  100.0f),
        glm::vec3(100.0f,  100.0f, -100.0f),
        glm::vec3(-100.0f,  100.0f, -100.0f)
    };

    std::vector<GLuint> indicies = {
        // Right
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3

    };

private:
    TextureStatus textureStatus = {false, false, ""};
    CompileStatus compileStatus = {false, false, ""};

    GLuint textureID;
    std::vector<Texture> requiredTextures;
    std::vector<unsigned char *> texturesData;

    Program program;


};

#endif // CUBEMAPTEXTURE_H
