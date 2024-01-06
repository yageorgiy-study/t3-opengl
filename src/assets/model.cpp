#include "model.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "../../include/tiny_obj_loader.h"
#include "../logger.h"

#include <random>
#include <algorithm>


Model::Model(std::string inputfile, std::string searchPathMTL)
{
    this->modelPath = inputfile;
	this->mtlPath = searchPathMTL;
}

Model::Model()
{
    this->modelPath = "";
	this->mtlPath = "";
}

Model::~Model()
{

}

const std::vector<glm::vec3> Model::getColors()
{
	return colors;
}

const std::vector<GLfloat> Model::getIndicies()
{
	return indicies;
}

const std::vector<glm::vec2> Model::getTextureCoords()
{
	return texture_coords;
}

const std::vector<glm::vec3> Model::getNormals()
{
	return normals;
}

const std::vector<glm::vec3> Model::getVertices()
{
	return vertices;
}

const std::string Model::getModelPath()
{
	return this->modelPath;
}

const std::string Model::getMTLPath()
{
	return this->mtlPath;
}

Data& Model::getData()
{
	return this->data;
}

void Model::loadModel()
{
	if(loaded) return;
	loaded = true;

	auto v = getVertices();
	auto n = getNormals();
	auto t = getTextureCoords();

	data = Data();
	data.init();
	data.vbo3v(v);
	data.vbo3v(n);
	data.vbo2v(t);
}

void Model::importModel()
{
    if(modelPath == "" || mtlPath == "") {
		return;
	}

	if(this->imported) return;
	this->imported = true;

    std::string inputfile = "./resources/models/" + modelPath;
    std::string searchPathMTL = "./resources/models/" + mtlPath;

	tinyobj::ObjReaderConfig reader_config;
    // Path to material files
	reader_config.mtl_search_path = searchPathMTL;
	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(inputfile, reader_config)) {
		if (!reader.Error().empty()) {
            Logger::message("SceneObject.importModel(): TinyObjReader: " + reader.Error());
		}
		return;
	}

	if (!reader.Warning().empty()) {
		Logger::message("SceneObject.importModel(): TinyObjReader: " + reader.Warning());
	}


	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();

	int j = 0;
	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {

				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
				tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
				tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];

                // Optional: vertex colors
				tinyobj::real_t red = attrib.colors[3*size_t(idx.vertex_index)+0];
				tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
				tinyobj::real_t blue = attrib.colors[3*size_t(idx.vertex_index)+2];

                vertices.push_back(glm::vec3(vx, vy, vz));
				colors.push_back(glm::vec3(red, green, blue));

				if (idx.normal_index >= 0) {
					tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
					tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
					tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];

					normals.push_back(glm::vec3(nx, ny, nz));
				}

				if (idx.texcoord_index >= 0) {
					tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
					tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];

					texture_coords.push_back(glm::vec2(tx, 1.0f - ty));
				}

				indicies.push_back(j);
				j++;
			}
			index_offset += fv;
		}
	}
}
