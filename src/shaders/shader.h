#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "compilestatus.h"

class Shader
{

public:
    Shader(std::string path, GLuint type);
    ~Shader();

    const static GLuint FRAGMET = GL_FRAGMENT_SHADER;
    const static GLuint VERTEX = GL_VERTEX_SHADER;

    const CompileStatus getCompileStatus();
    const GLuint getType();
    // const GLuint getGlId();
    const std::string getPath();

    void loadSourceFile();
    void compile();
    void unloadShader();

    GLuint glId = 0;
private:
    void setCompileStatus(bool compiled, bool failed, std::string status);

    std::string path = "";
    std::string sourceCode = "";
    GLuint type = GL_FRAGMENT_SHADER;
    CompileStatus compileStatus = {false, false, ""};

};

#endif // SHADER_H


