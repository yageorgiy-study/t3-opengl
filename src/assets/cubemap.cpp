#include "cubemap.h"


CubeMap::CubeMap()
{
    this->requireCubemapTextures({
        "skybox/right.png",
		"skybox/left.png",
		"skybox/top.png",
		"skybox/bottom.png",
		"skybox/front.png",
		"skybox/back.png",
    });
}

CubeMap::~CubeMap()
{

}

void CubeMap::requireCubemapTextures(std::initializer_list<std::string> list)
{
    for(auto item : list) {
        this->requiredTextures.push_back(Texture(item));
    }
}

void CubeMap::importTextures()
{
    for(auto& item : requiredTextures) {
        item.import();
        TextureStatus status = item.getStatus();
        if(status.failed){
            this->textureStatus = status;
            return;
        }
    }

    this->textureStatus = {true, false, ""};
}

void CubeMap::load()
{
    if(this->textureStatus.failed) return;

    // Загрузка текстур специфичным для скайбокса образом

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    int i = 0;
    for(auto& item : requiredTextures) {
        if(!item.getStatus().failed) {
            // std::cout << "DEBUG: " << i << " " << item.getWidth() << " " << item.getHeight() << "\n";
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, item.getWidth(), item.getHeight(),
                0, GL_RGB, GL_UNSIGNED_BYTE, item.getImage()
            );
        }
        i++;
    }

    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Сборка данных для программы и самой программы
    // TODO: объединить создание Data, Shader и Program с SceneObject (?)
    Data data;
    data.vbo3v(vertices);
    data.ibo(indicies);

	auto fs = Shader("skybox.fs", Shader::FRAGMET);
	auto vs = Shader("skybox.vs", Shader::VERTEX);

    program = Program(data);
    program.setDrawingMethod(DrawMethod::ELEMENTS);
    program.setDrawPrimitivesType(Program::TRIANGLES);
    program.setPrimitivesCount(indicies.size());
    // program.setPrimitivesCount(36);
    program.addShader(fs);
	program.addShader(vs);

    // Сразу же компилируем
    program.compile();
    CompileStatus cs = program.getCompileStatus();
    if(cs.failed){
        compileStatus = cs;
        return;
    }

    compileStatus = {true, false, ""};
}


const Program CubeMap::getProgram()
{
    return this->program;
}


const CompileStatus CubeMap::getCompileStatus()
{
    return this->compileStatus;
}

const TextureStatus CubeMap::getTextureStatus()
{
    return this->textureStatus;
}


void CubeMap::render(const glm::mat4 matrixProjection, const glm::mat4 matrixView, const glm::vec3 cameraPosition)
{
    if(compileStatus.failed || textureStatus.failed) return;

    glDepthFunc(GL_LEQUAL);

    // ВАЖНО ИСПОЛЬЗОВАТЬ ПРОГРАММУ ПЕРЕД УСТАНОВКОЙ АРГУМЕНТОВ!!!
    program.use();


    // Назначение аргументов
    program.setArgument1iValue("skybox", 0);
    program.setArgument1fValue("iTime", glfwGetTime());
    program.setArgumentMatrix4fvValue("projection", matrixProjection);
    program.setArgumentMatrix4fvValue("view", matrixView);


    // Активация текстур
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // Отрисовка скайбокса
    program.run();

    glDepthFunc(GL_LESS);
}

