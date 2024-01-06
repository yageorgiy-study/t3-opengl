#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * @todo write docs
 */
class Data
{
public:
    // GLsizei objectsCount,
    static Data ofVBO3v(std::initializer_list<std::vector<glm::vec3>> list);
    static Data ofVBO2v(std::initializer_list<std::vector<glm::vec2>> list);
    static Data ofIBO(std::initializer_list<std::vector<GLuint>> list);

public:
    /**
     * Constructors
     */
    // Data(GLsizei objectsCount);
    Data();

    /**
     * Destructor
     */
    ~Data();

    const GLsizei getObjectsCount();

    GLuint vbo3v(
        std::vector<glm::vec3> array,
        GLuint bufferType = GL_STATIC_DRAW
    );
    GLuint vbo2v(
        std::vector<glm::vec2> array,
        GLuint bufferType = GL_STATIC_DRAW
    );
    GLuint ibo(
        std::vector<GLuint> indices,
        GLuint bufferType = GL_STATIC_DRAW
    );

    void init();

    // void setObjectsCount(GLsizei objectsCount);

    void apply();
    void reset();

    GLuint getVaoId();

private:
    GLuint vaoId = 0;

    template<typename T>
    GLuint vbo(
        std::vector<T> array,
        GLuint componentSize,
        GLuint bufferType = GL_STATIC_DRAW
    );

    GLuint lastVBOid = 0;
    GLuint iboId = 0;
    // GLsizei objectsCount = 0;
};

#endif // DATA_H
