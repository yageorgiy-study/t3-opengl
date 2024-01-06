#include "program.h"
#include "./../logger.h"
#include <sstream>
#include <iostream>

/* Конструктор */

Program::Program()
{

}

Program::Program(Data data)
{
    this->data = data;
}


/* Деструктор */

Program::~Program()
{

    for(Shader shader : shaders)
        shader.unloadShader();

    this->unload();

    // if(this->compileStatus.errorText != nullptr)
    //     delete this->compileStatus.errorText;
}

/* Геттеры */

GLint Program::getArgumentPointer(std::string argumentName)
{
    if(!compileStatus.compiled || compileStatus.failed) return 0;
    // TODO: запоминать уже найденные идентификаторы в программе

    // auto loc = ;
    // std::cout << "Test: " << this->glId << " " << loc << "\n";
    return glGetUniformLocation(this->glId, argumentName.c_str());
}

const CompileStatus Program::getCompileStatus()
{
    return this->compileStatus;
}

const std::vector<Shader> Program::getShaders()
{
    return this->shaders;
}

const DrawMethod Program::getDrawMethod()
{
    return this->drawMethod;
}

const GLuint Program::getPrimitivesCount()
{
    return this->primitivesCount;
}

const GLuint Program::getPrimitivesType()
{
    return this->drawPrimitiveType;
}

const GLuint Program::getId()
{
    return this->glId;
}



/* Сеттеры */

void Program::addShader(Shader shader)
{
    this->shaders.push_back(shader);
}

void Program::setData(Data data)
{
    this->data = data;
}


void Program::setArgumentMatrix4fvValue(std::string argumentName, glm::mat4 value)
{
    if(!compileStatus.compiled || compileStatus.failed) return;
    glUniformMatrix4fv(this->getArgumentPointer(argumentName), 1, GL_FALSE, &value[0][0]);
}

void Program::setArgument3fvValue(std::string argumentName, glm::vec3 value)
{
    if(!compileStatus.compiled || compileStatus.failed) return;
    glUniform3fv(this->getArgumentPointer(argumentName), 1, &value[0]);
}

void Program::setArgument1iValue(std::string argumentName, int value)
{
    if(!compileStatus.compiled || compileStatus.failed) return;
    glUniform1i(this->getArgumentPointer(argumentName), value);
}

void Program::setArgument1fValue(std::string argumentName, float value)
{
    if(!compileStatus.compiled || compileStatus.failed) return;
    glUniform1f(this->getArgumentPointer(argumentName), value);
}




void Program::setPrimitivesCount(GLuint count)
{
    this->primitivesCount = count;
}

void Program::setDrawPrimitivesType(GLuint drawObjectType)
{
    this->drawPrimitiveType = drawObjectType;
}

void Program::setDrawingMethod(DrawMethod method)
{
    this->drawMethod = method;
}


void Program::setCompileStatus(bool compiled, bool failed, std::string status)
{
    // if(this->compileStatus.errorText != nullptr)
    //     delete this->compileStatus.errorText;
    // this->compileStatus.errorText = nullptr;
    this->compileStatus.compiled = compiled;
    this->compileStatus.failed = failed;
    this->compileStatus.errorText = status;
}


/* Действия */

void Program::unload()
{
    if(!compileStatus.compiled) return;
    glDeleteProgram(glId);
    setCompileStatus(false, false, "");
}


// void Program::setArgumentValue(std::string argumentName, GLuint* valuePointer)
// {
//
// }

void Program::use()
{
    data.apply();
    glUseProgram(glId);
}



void Program::run()
{
    if(!compileStatus.compiled || compileStatus.failed) return;

    switch(drawMethod){
        case ARRAY:
        default:
            glDrawArrays(drawPrimitiveType, 0, this->primitivesCount);
            break;

        case ELEMENTS:
            glDrawElements(drawPrimitiveType, this->primitivesCount, GL_UNSIGNED_INT, 0);
            break;
    }

    data.reset();
}

void Program::compile()
{
    // Если уже была попытка компиляции программы, то отменяем загрузку
    if(compileStatus.compiled) return;



    // Компиляция каждого отдельного шейдера
    int i = 1;
    for(Shader& shader : shaders) {
        // Logger::message("fgfdgdffg");
        shader.compile();


        CompileStatus status = shader.getCompileStatus();
        if(status.failed){

            std::stringstream ss;
            ss << "Could not prepare program due to failed ";
            ss << "shader compilation ";
            ss << "(" << i << " of " << shaders.size() << "): ";
            ss << status.errorText;

            setCompileStatus(true, true, ss.str());
            return;
        }
        i++;
    }

    // Связка в отдельную программу
    glId = glCreateProgram();
    for(Shader& shader : shaders) {
        glAttachShader(glId, shader.glId);
    }
    glLinkProgram(glId);

    GLint result = GL_FALSE;
    int infoLogLength;

    glGetProgramiv(glId, GL_LINK_STATUS, &result);
    glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &infoLogLength);

    // if (infoLogLength > 0) {
    if (result == GL_FALSE) {
        char* errorMessage = new char[infoLogLength + 1];
        glGetProgramInfoLog(glId, infoLogLength, NULL, errorMessage);

        std::stringstream ss;
            ss << "Program linking error: ";
            ss << errorMessage;

        delete[] errorMessage;

        setCompileStatus(true, true, ss.str());

        return;
    }


    // Очистка шейдеров
    for(Shader& shader : shaders)
        shader.unloadShader();

    setCompileStatus(true, false, "");
}
