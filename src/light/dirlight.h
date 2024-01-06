#pragma once

#ifndef DIRLIGHT_H
#define DIRLIGHT_H

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @todo write docs
 */
class DirLight
{
public:
    /**
     * Default constructor
     */
    DirLight();

    /**
     * Destructor
     */
    ~DirLight();

    glm::vec3 specular;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 direction;
};

#endif // DIRLIGHT_H
