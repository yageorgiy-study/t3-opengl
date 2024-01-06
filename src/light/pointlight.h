#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @todo write docs
 */
class PointLight
{
public:
    /**
     * Default constructor
     */
    PointLight();

    /**
     * Destructor
     */
    ~PointLight();

    glm::vec3 specular;
    glm::vec3 diffuse;
    glm::vec3 ambient;

    float quadratic;
    float linear;
    float constant;

    glm::vec3 position;
};

#endif // POINTLIGHT_H
