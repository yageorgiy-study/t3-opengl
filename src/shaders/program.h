#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "shader.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "data.h"
#include "drawmethod.h"
#include "compilestatus.h"
#include "argumenttype.h"

class Program
{

public:
    Program();
    Program(Data data);
    ~Program();

    const static GLuint TRIANGLES = GL_TRIANGLES;

    const std::vector<Shader> getShaders();
    const CompileStatus getCompileStatus();
    const DrawMethod getDrawMethod();
    const GLuint getPrimitivesType();
    const GLuint getPrimitivesCount();
    const GLuint getId();

    void addShader(Shader shader);
    void setData(Data data);
    void setDrawingMethod(DrawMethod method);
    void setDrawPrimitivesType(GLuint drawObjectType);

    void setArgumentMatrix4fvValue(std::string argumentName, glm::mat4 value);
    void setArgument3fvValue(std::string argumentName, glm::vec3 value);
    void setArgument1iValue(std::string argumentName, int value);
    void setArgument1fValue(std::string argumentName, float value);


    void setPrimitivesCount(GLuint count);

    void compile();
    void unload();
    void use();
    void run();
    // void use();

    // std::string asdsdadas = "";

private:
    void setCompileStatus(bool compiled, bool failed, std::string status);

    std::vector<Shader> shaders;
    Data data;
    CompileStatus compileStatus = {false, false, ""};
    GLuint glId = 0;
    GLuint drawPrimitiveType = GL_TRIANGLES;
    DrawMethod drawMethod = ARRAY;
    GLuint primitivesCount = 0;

    // void setArgumentValue(std::string argumentName, GLuint* valuePointer);
    GLint getArgumentPointer(std::string argumentName);
};

#endif // PROGRAM_H

