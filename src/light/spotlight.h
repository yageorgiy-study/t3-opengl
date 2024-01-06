#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @todo write docs
 */
class SpotLight
{
public:
    /**
     * Default constructor
     */
    SpotLight();

    /**
     * Destructor
     */
    ~SpotLight();

    glm::vec3 specular;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    float quadratic;
    float linear;
    float constant;
    float outerCutOff;
    float cutOff;
    glm::vec3 direction;
    glm::vec3 position;
};

#endif // SPOTLIGHT_H
