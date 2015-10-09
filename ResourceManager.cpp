#include "include/ResourceManager.h"


std::unordered_map<std::string, ShaderProgram> ResourceManager::shaders;
std::unordered_map<std::string, Texture> ResourceManager::textures;

ShaderProgram ResourceManager::load_shader(const std::string vertex,
                const std::string fragment, const std::string name){
    ShaderProgram program(vertex, fragment);
    shaders[name] = program;
    return shaders[name]; 
}



