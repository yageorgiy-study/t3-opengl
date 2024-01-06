#include "material.h"

Material::Material()
{
    texture = Texture("generic/generic.png");
	specularMapTexture = Texture("generic/generic.spec.png");
}

Material::~Material()
{

}

bool Material::hasRequiredSpecularMapTextureName()
{
    return this->requiredSpecularMapTextureName != "";
}

bool Material::hasRequiredTextureName()
{
    return this->requiredTextureName != "";
}

