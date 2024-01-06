#ifndef LIGHTSINFO_H
#define LIGHTSINFO_H

#include <stdio.h>
#include <vector>
#include "spotlight.h"
#include "pointlight.h"
#include "dirlight.h"

/**
 * @todo write docs
 */
class LightsInfo
{
public:
    /**
     * Default constructor
     */
    LightsInfo();

    /**
     * Destructor
     */
    ~LightsInfo();

    std::vector<SpotLight> spotLights;
    std::vector<PointLight> pointLights;
    DirLight dirLight;
};

#endif // LIGHTSINFO_H
