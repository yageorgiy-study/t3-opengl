#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "texturestatus.h"

/**
 * @todo write docs
 */
class Texture
{
public:
    /**
     * Default constructor
     */
    Texture();

    Texture(std::string filename);

    /**
     * Destructor
     */
    ~Texture();

    // Геттеры
    const TextureStatus getStatus();
    const std::string getFilename();
    const GLuint getGlId();
    const unsigned char* getImage();
    const int getHeight();
    const int getWidth();

    // Действия
    void import();
    void load();
    void activate();
    void deactivate();
    void clean();

private:
    TextureStatus status = {false, false, ""};
    bool loaded = false;

    std::string filename = "";
    GLuint glId;
    unsigned char* image = NULL;
    int height = 0;
    int width = 0;

};

#endif // TEXTURE_H
