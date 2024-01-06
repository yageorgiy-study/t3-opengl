#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"

/**
 * @todo write docs
 */
class Material
{
public:
    /**
     * Default constructor
     */
    Material();

    /**
     * Destructor
     */
    ~Material();

    // TODO: инкапсулировать texture и specularMapTexture

    float shininess;
    glm::vec3 ambient;
	glm::vec3 diffuse;
    glm::vec3 specular;
    Texture specularMapTexture;
    Texture texture;

    std::string requiredTextureName = "";
    std::string requiredSpecularMapTextureName = "";


    bool hasRequiredTextureName();
    bool hasRequiredSpecularMapTextureName();
};

#endif // MATERIAL_H
