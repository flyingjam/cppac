#include "include/ResourceManager.h"


std::unordered_map<std::string, ShaderProgram> ResourceManager::shaders;
std::unordered_map<std::string, Texture> ResourceManager::textures;

ShaderProgram ResourceManager::load_shader(const std::string& vertex,
                const std::string& fragment, std::string name){
    ShaderProgram program(vertex, fragment);
    shaders[name] = program;
    return shaders[name]; 
}

ShaderProgram ResourceManager::get_shader(std::string name){
    return shaders[name];
}

Texture ResourceManager::load_texture(const std::string& path, std::string name){
    Texture tex(path);
    textures[name] = tex;
    return textures[name]; 
}

Texture ResourceManager::get_texture(std::string name){
    return textures[name];
}

void ResourceManager::clear(){
    for (auto iter : shaders)
        glDeleteProgram(iter.second.ID);
    for (auto iter : textures)
        glDeleteTextures(1, &iter.second.ID);
}
