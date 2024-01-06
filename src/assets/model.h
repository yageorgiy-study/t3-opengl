#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "../shaders/data.h"
#include <vector>

/**
 * @todo write docs
 */
class Model
{
public:
    /**
     * Default constructor
     */
    Model();
    Model(std::string modelPath, std::string mtlPath);

    /**
     * Destructor
     */
    ~Model();

    void importModel(); // To RAM
    void loadModel();   // To GPU

    const std::vector<glm::vec3> getVertices();
    const std::vector<glm::vec3> getNormals();
    const std::vector<glm::vec2> getTextureCoords();
    const std::vector<glm::vec3> getColors();
	const std::vector<GLfloat>   getIndicies();

	const std::string   getModelPath();
	const std::string   getMTLPath();

    Data& getData();
private:
    Data data;

    bool imported = false; // In RAM
    bool loaded = false; // By GPU

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texture_coords;
    std::vector<glm::vec3> colors;
	std::vector<GLfloat> indicies;

    std::string modelPath = "";
    std::string mtlPath = "";
};

#endif // MODEL_H
