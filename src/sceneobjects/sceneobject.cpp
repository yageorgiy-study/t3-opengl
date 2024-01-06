#include "sceneobject.h"
// #define TINYOBJLOADER_IMPLEMENTATION
// #include "../../include/tiny_obj_loader.h"
#include "../logger.h"

#include <random>
#include <algorithm>


SceneObject::SceneObject()
{
	// this->textures = std::vector<Texture>();
	this->programmes = std::vector<Program>();

	this->lights.dirLight.direction = glm::vec3(1.0f, 1.0f, 1.0f);
    this->lights.dirLight.ambient 	= glm::vec3(0.0f, 0.0f, 0.0f);
    this->lights.dirLight.diffuse 	= glm::vec3(1.0f, 1.0f, 1.0f);
    this->lights.dirLight.specular 	= glm::vec3(0.8f, 0.8f, 0.8f);

	PointLight pl;
	pl.position = glm::vec3(1.0f, 1.0f, 1.0f);
    pl.constant = 1.0f;
    pl.linear = 0.0f;
    pl.quadratic = 0.01f;
    pl.ambient = glm::vec3(0.8f, 0.0f, 0.0f);
    pl.diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
    pl.specular = glm::vec3(0.2f, 0.2f, 0.2f);
	// lights.pointLights.push_back(pl);

	SpotLight sl;
	sl.position = glm::vec3(0.0f, -1.0f, 1.0f);
    sl.direction = glm::vec3(1.0f, 1.0f, 0.0f);
    sl.constant = 1.0f;
    sl.linear = 0.07f;
    sl.quadratic = 0.02f;
    sl.ambient = glm::vec3(0.8f, 0.7f, 0.0f);
    sl.diffuse = glm::vec3(0.0f, 1.0f, 0.0f);
    sl.specular = glm::vec3(0.0f, 1.0f, 0.0f);
    sl.cutOff = cos(glm::radians(20.0f));
    sl.outerCutOff = cos(glm::radians(20.0f));
	// lights.spotLights.push_back(sl);


	material.shininess = 0.6f;
	material.ambient = glm::vec3(0.8f, 0.8f, 0.8f);
    material.diffuse = glm::vec3(0.5f, 0.8f, 0.0f);
	material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	material.texture = Texture("generic/generic.png");
	material.requiredTextureName = "__generic__";
	material.specularMapTexture = Texture("generic/generic.spec.png");
	material.requiredSpecularMapTextureName = "__generic_specular__";
}

SceneObject::~SceneObject()
{

}

// const std::vector<Program> SceneObject::getProgrammes()
// {
//     return this->programmes;
// }
//
// const std::vector<Texture> SceneObject::getTextures()
// {
//     return this->textures;
// }

void SceneObject::addProgram(Program program)
{
    this->programmes.push_back(program);
}

// void SceneObject::addTextures(Texture texture)
// {
//     this->textures.push_back(texture);
// }

void SceneObject::requireModel(std::string modelName)
{
	this->modelName = modelName;
}

bool SceneObject::hasModelRequired()
{
	return this->modelName != "";
}

const std::string SceneObject::getModelName()
{
	return this->modelName;
}



void SceneObject::applyModel(Model& model)
{
	model.loadModel();
	Data& data = model.getData();

	auto fs = Shader("object.fs", Shader::FRAGMET);
	auto vs = Shader("object.vs", Shader::VERTEX);

	// TODO: разъединить программу и данные (но тогда нужно разъединить и primitivesCount)
	// TODO: прикреплять к SceneObject объект Model (?)

	Program program(data);
    program.setDrawPrimitivesType(Program::TRIANGLES);
    program.setPrimitivesCount(model.getVertices().size());
    program.addShader(fs);
	program.addShader(vs);

    this->addProgram(program);
}


glm::mat4 SceneObject::matrixModel(const glm::vec3 cameraPosition)
{

    glm::mat4 model(1.0);

	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	// model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));






	if(this->simpleAnimation){
		model = glm::rotate(model, glm::radians(tmp* 1000), glm::vec3(0.0f, 1.0f, 0.0f));
		this->tmp += 0.005f;
	}

	return model;
}

void SceneObject::render(const glm::mat4 matrixProjection, const glm::mat4 matrixView, const glm::vec3 cameraPosition)
{

	glm::mat4 model = matrixModel(cameraPosition);

    for(Program& program : programmes)
    {
		// ВАЖНО ИСПОЛЬЗОВАТЬ ПРОГРАММУ ПЕРЕД УСТАНОВКОЙ АРГУМЕНТОВ!!!
		program.use();

		program.setArgument3fvValue("lights.dirLight.direction", this->lights.dirLight.direction);
		program.setArgument3fvValue("lights.dirLight.ambient", this->lights.dirLight.ambient);
		program.setArgument3fvValue("lights.dirLight.diffuse", this->lights.dirLight.diffuse);
		program.setArgument3fvValue("lights.dirLight.specular", this->lights.dirLight.specular);

		/* Point lights */
		program.setArgument1iValue("lights.numPLights", (int)this->lights.pointLights.size());
		for (int i = 0; i < this->lights.pointLights.size(); i++)
		{
			program.setArgument3fvValue(
				(std::string( "lights.pointLights[") + std::to_string(i) + "].position"),
				lights.pointLights[i].position
			);

			program.setArgument1fValue(
				(std::string("lights.pointLights[") + std::to_string(i) + "].constant"),
				lights.pointLights[i].constant
			);

			program.setArgument1fValue(
				(std::string("lights.pointLights[") + std::to_string(i) + "].linear"),
				lights.pointLights[i].linear
			);

			program.setArgument1fValue(
				(std::string("lights.pointLights[") + std::to_string(i) + "].quadratic"),
				lights.pointLights[i].quadratic
			);

			program.setArgument3fvValue(
				(std::string( "lights.pointLights[") + std::to_string(i) + "].ambient"),
				lights.pointLights[i].ambient
			);

			program.setArgument3fvValue(
				(std::string( "lights.pointLights[") + std::to_string(i) + "].diffuse"),
				lights.pointLights[i].diffuse
			);

			program.setArgument3fvValue(
				(std::string( "lights.pointLights[") + std::to_string(i) + "].specular"),
				lights.pointLights[i].specular
			);
		}

		/* Spot lights */
		program.setArgument1iValue("lights.numSLights", (int)this->lights.spotLights.size());

		for (int i = 0; i < lights.spotLights.size(); i++)
		{
			program.setArgument3fvValue(
				(std::string( "lights.spotLights[") + std::to_string(i) + "].position"),
				lights.spotLights[i].position
			);

			program.setArgument3fvValue(
				(std::string( "lights.spotLights[") + std::to_string(i) + "].direction"),
				lights.spotLights[i].direction
			);

			program.setArgument1fValue(
				(std::string( "lights.spotLights[") + std::to_string(i) + "].constant"),
				lights.spotLights[i].constant
			);

			program.setArgument1fValue(
				(std::string( "lights.spotLights[") + std::to_string(i) + "].linear"),
				lights.spotLights[i].linear
			);

			program.setArgument1fValue(
				(std::string( "lights.spotLights[") + std::to_string(i) + "].quadratic"),
				lights.spotLights[i].quadratic
			);

			program.setArgument3fvValue(
				(std::string( "lights.spotLights[") + std::to_string(i) + "].ambient"),
				lights.spotLights[i].ambient
			);

			program.setArgument3fvValue(
				(std::string( "lights.spotLights[") + std::to_string(i) + "].diffuse"),
				lights.spotLights[i].diffuse
			);

			program.setArgument3fvValue(
				(std::string( "lights.spotLights[") + std::to_string(i) + "].specular"),
				lights.spotLights[i].specular
			);

			program.setArgument1fValue(
				(std::string( "lights.spotLights[") + std::to_string(i) + "].cutOff"),
				lights.spotLights[i].cutOff
			);

			program.setArgument1fValue(
				(std::string( "lights.spotLights[") + std::to_string(i) + "].outerCutOff"),
				lights.spotLights[i].outerCutOff
			);

		}

		/* Material */
		program.setArgument1iValue("material.texture", material.texture.getGlId());
		program.setArgument1iValue("material.specularmap", material.specularMapTexture.getGlId());

		program.setArgument3fvValue("material.ambient", material.ambient);
		program.setArgument3fvValue("material.diffuse", material.diffuse);
		program.setArgument3fvValue("material.specular", material.specular);
		program.setArgument1fValue("material.shininess", material.shininess);

		/* Позиция камеры */
		program.setArgument3fvValue("campos", cameraPosition);

		program.setArgumentMatrix4fvValue("projection", matrixProjection);
		program.setArgumentMatrix4fvValue("view", matrixView);
		program.setArgumentMatrix4fvValue("model", model);

		// debugProgram(program);

		material.texture.activate();
		material.specularMapTexture.activate();

		program.run();

		glBindTexture(GL_TEXTURE_2D, 0);
    }
}

/* Program debug (OPTIONAL) */

void SceneObject::debugProgram(Program program)
{
	GLint i;
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 128; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length

	glGetProgramiv(program.getId(), GL_ACTIVE_ATTRIBUTES, &count);
	printf("Active Attributes: %d\n", count);

	for (i = 0; i < count; i++)
	{
		glGetActiveAttrib(program.getId(), (GLuint)i, bufSize, &length, &size, &type, name);

		printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
	}

	glGetProgramiv(program.getId(), GL_ACTIVE_UNIFORMS, &count);
	printf("Active Uniforms: %d\n", count);

	for (i = 0; i < count; i++)
	{
		glGetActiveUniform(program.getId(), (GLuint)i, bufSize, &length, &size, &type, name);

		printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
	}

}
