#include "data.h"
#include "../logger.h"

// TODO: реализовать выгрузку объектов только после 100% создания opengl-контекста
// TODO: реализовать выгрузку объектов только после 100% создания opengl-контекста
// TODO: реализовать выгрузку объектов только после 100% создания opengl-контекста


Data Data::ofIBO(std::initializer_list<std::vector<GLuint>> list)
{
    // GLsizei objectsCount,
    Data data;
    // data.setObjectsCount(objectsCount);
    for(auto vec : list){
        data.ibo(vec);
    }
    return data;
}

Data Data::ofVBO2v(std::initializer_list<std::vector<glm::vec2>> list)
{
    //GLsizei objectsCount,
    Data data;
    // data.setObjectsCount(objectsCount);
    for(auto vec : list){
        data.vbo2v(vec);
    }
    return data;
}

Data Data::ofVBO3v(std::initializer_list<std::vector<glm::vec3>> list)
{
    Data data;
    // GLsizei objectsCount,
    // data.setObjectsCount(objectsCount);
    for(auto vec : list){
        data.vbo3v(vec);
    }
    return data;
}

// GLsizei objectsCount
Data::Data()
{
    // this->objectsCount = objectsCount;
}

// Data::Data()
// {
    // this->objectsCount = 0;
// }

Data::~Data()
{
    // TODO: remove VAO, VBOs, IBOs??
}

GLuint Data::getVaoId()
{
    return this->vaoId;
}

void Data::init()
{
    glGenVertexArrays(1, &this->vaoId);
}

void Data::apply()
{
    glBindVertexArray(vaoId);
    if(iboId > 0){
        // std::cout << iboId << "\n";
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    }
}

void Data::reset()
{
    glBindVertexArray(0);
    if(iboId > 0){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

GLuint Data::ibo(std::vector<GLuint> indices, GLuint bufferType)
{
    glBindVertexArray(vaoId);

    glGenBuffers(1, &iboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), bufferType);

    glBindVertexArray(0);

    return iboId;
}

GLuint Data::vbo2v(std::vector<glm::vec2> array, GLuint bufferType)
{
    return this->vbo<glm::vec2>(array, 2, bufferType);
}

GLuint Data::vbo3v(std::vector<glm::vec3> array, GLuint bufferType)
{
    return this->vbo<glm::vec3>(array, 3, bufferType);
}

template<typename T>
GLuint Data::vbo(std::vector<T> array, GLuint componentSize, GLuint bufferType)
{
    glBindVertexArray(vaoId);

    // GLint asd[array.size()]

    GLuint vboId = 0;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    // glBufferData(GL_ARRAY_BUFFER, array.size() * sizeof(T), &array[0], bufferType);
    glBufferData(GL_ARRAY_BUFFER, array.size() * sizeof(T), array.data(), bufferType);
    // glBufferData(GL_ARRAY_BUFFER, array.size() * sizeof(GLfloat), &array[0], bufferType);

    // std::vector<glm::vec3> asdsdasda;
    // asdsdasda = {
    //     {
    //         1.0f, 1.0f, 1.0f
    //     }
    // };
    // asdsdasda.push_back
    // std::cout << array.size() << "\n";
    // std::cout << typeid(T).name() << "\n";
    // std::cout <<  array.size() * sizeof(T) << "\n";
    // std::cout << array.size() * 2 * sizeof(GLfloat) << "\n";

    glVertexAttribPointer(lastVBOid, componentSize, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(lastVBOid);

    // glBindVertexArray(0);

    lastVBOid++;

    return vboId;
}


// void Data::setObjectsCount(GLsizei objectsCount)
// {
//     this->objectsCount = objectsCount;
// }
//
// const GLsizei Data::getObjectsCount()
// {
//     return objectsCount;
// }
