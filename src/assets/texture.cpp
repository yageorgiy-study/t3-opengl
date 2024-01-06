#include "texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>
#include <iostream>

/* Конструкторы */

Texture::Texture()
{

}

Texture::Texture(std::string filename)
{
    this->filename = filename;
}

/* Деструктор */

Texture::~Texture()
{
    if(image != NULL)
        SOIL_free_image_data(image);
}

/* Геттеры */

const TextureStatus Texture::getStatus()
{
    return this->status;
}

const std::string Texture::getFilename()
{
    return this->filename;
}

const GLuint Texture::getGlId()
{
    return this->glId;
}

const unsigned char* Texture::getImage()
{
    return this->image;
}

const int Texture::getHeight()
{
    return this->height;
}

const int Texture::getWidth()
{
    return this->width;
}

/* Действия */

void Texture::import()
{
    // Если уже была попытка загрузки, то перестаем загружать
    if(status.imported) return;

    std::string fullFileName = "./resources/textures/" + filename;

    image = SOIL_load_image(fullFileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    if(image == NULL)
    {
        status = {
            true,
            true,
            fullFileName + ": " + SOIL_last_result()
        };

        // ?
        SOIL_free_image_data(image);
        return;
    }

    // std::cout << "Texture import done " << fullFileName << " @ " << &image << "\n";

    status = {
        true,
        false,
        ""
    };
}


void Texture::load()
{
    // Если уже была попытка загрузки, то перестаем загружать
    if(loaded) return;
    if(!status.imported) return;

    glGenTextures(1, &glId);
    glBindTexture(GL_TEXTURE_2D, glId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    clean();

    // std::cout << "Texture load done " << &image << "\n";

    loaded = true;
}

void Texture::clean()
{
    // Очищаем после загрузки, чтобы не тратить лишнюю оперативную память
    SOIL_free_image_data(image);
    image = nullptr;
}

void Texture::activate()
{
    if(!status.imported) return;
    // std::cout << "Loaded!" << glId << "\n";
    // glEnable(GL_TEXTURE0 + glId);
    // glActiveTexture(GL_TEXTURE0 + glId);
    glActiveTexture(GL_TEXTURE0 + glId);
    // glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, glId);
}

void Texture::deactivate()
{
    if(!status.imported) return;
    // std::cout << "Loaded!" << glId << "\n";
    // glActiveTexture(GL_TEXTURE0 + glId);
    // glBindTexture(GL_TEXTURE_2D, 0);
}
