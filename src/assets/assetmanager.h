#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <iostream>
#include <map>
#include "material.h"
#include "model.h"
#include "../shaders/program.h"

/**
 * @todo write docs
 */
class AssetManager
{
public:
    /**
     * Default constructor
     */
    AssetManager();

    /**
     * Destructor
     */
    ~AssetManager();

    void addModel(std::string name, std::string folder, std::string modelFileName);
    void addTexture(std::string name, std::string texturePath);
    // void addProgram(std::string name, std::string texturePath);

    Model&   getModel(std::string name);
    Texture& getTexture(std::string name);
    // Program& getProgram(std::string name);

    typedef std::map<std::string, Model>   ModelsMap;
    typedef std::map<std::string, Texture> TexturesMap;
    // typedef std::map<std::string, Program> ProgramMap;
    ModelsMap   models;
    TexturesMap textures;
    // ProgramMap  programmes;

private:
    Model   genericModel;
    Texture genericTexture;
    // Program genericProgram;

};

#endif // ASSETMANAGER_H
