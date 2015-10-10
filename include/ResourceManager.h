#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Texture.h"
#include "ShaderProgram.h"

#include <vector>
#include <map>
#include <string>
#include <unordered_map>

class ResourceManager{
    public:

        static std::unordered_map<std::string, ShaderProgram> shaders;
        static std::unordered_map<std::string, Texture> textures;

        static ShaderProgram load_shader(const std::string& vertex,
                const std::string& fragment, const std::string& name);
        static ShaderProgram get_shader(const std::string& name);

        static Texture load_texture(const std::string& path, const std::string& name);
        static Texture get_texture(const std::string& name); 

        static void clear();
    private:
        ResourceManager() {}
};

#endif

