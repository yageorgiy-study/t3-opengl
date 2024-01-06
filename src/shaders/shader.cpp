#include "shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../logger.h"

/* Конструктор */

Shader::Shader(std::string path, GLuint type)
{
    this->path = "./resources/shaders/" + path;
    this->type = type;
}

/* Деструктор */

Shader::~Shader()
{
    this->unloadShader();

    // if(this->compileStatus.errorText != nullptr)
    //     delete this->compileStatus.errorText;
}

/* Геттеры */

const CompileStatus Shader::getCompileStatus()
{
    return this->compileStatus;
}

// const GLuint Shader::getGlId()
// {
//     return this->glId;
// }

const GLuint Shader::getType()
{
    return this->type;
}

const std::string Shader::getPath()
{
    return this->path;
}


/* Сеттеры */

void Shader::setCompileStatus(bool compiled, bool failed, std::string status)
{
    // if(this->compileStatus.errorText != nullptr) {
    //     delete this->compileStatus.errorText;
    // }
    // this->compileStatus.errorText = nullptr;
    this->compileStatus.compiled = compiled;
    this->compileStatus.failed = failed;
    this->compileStatus.errorText = status;
}


/* Действия */

void Shader::compile()
{
    this->loadSourceFile();

    if(sourceCode == "") {
        setCompileStatus(
            true,
            true,
            ("Empty shader source code "
            "(could not load file or got zero bytes)")
        );
        return;
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    const char* vertex_shader = sourceCode.c_str();

    glId = glCreateShader(this->type);
    glShaderSource(glId, 1, &vertex_shader, NULL);
    glCompileShader(glId);


    // Если ошибка
    glGetShaderiv(glId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(glId, GL_INFO_LOG_LENGTH, &infoLogLength);

    // if (infoLogLength > 0) {
    if (result == GL_FALSE) {
        char* errorMessage = new char[infoLogLength + 1];

        glGetShaderInfoLog(glId, infoLogLength, NULL, errorMessage);

        setCompileStatus(true, true, std::string(errorMessage));
        delete[] errorMessage;

        glDeleteShader(glId);
        glId = 0;
        return;
    }

    setCompileStatus(true, false, "");
}

void Shader::loadSourceFile()
{
    std::ifstream file(path, std::ios::in);
    if (file.is_open()) {
        std::stringstream sstr;
        sstr << file.rdbuf();
        sourceCode = sstr.str();
        file.close();
    } else {
        sourceCode = "";
    }
}


void Shader::unloadShader()
{
    if(!compileStatus.compiled) return;
    glDeleteShader(glId);
    sourceCode = "";
    glId = 0;

    setCompileStatus(false, false, "");

}
