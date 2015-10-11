#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "glad.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram{
    private:

        GLint get_uniform_location(const std::string& uniform);
        std::string read_shader(const std::string& filename);
        GLuint create_shader(GLenum shader_type, std::string source);
        GLuint create_program(const std::string& vertex, const std::string& fragment);

    public:
        GLuint ID; 
        ShaderProgram();
        ShaderProgram& Use();
        ShaderProgram(const std::string& vertex, const std::string& fragment);
        void set_program(const std::string& vertex, const std::string& fragment); 
        void set_float(const std::string& name, const float value, bool use_shader);
        void set_vec4(const std::string& name, const glm::vec4& value, bool use_shader);
        void set_mat4(const std::string& name, const glm::mat4& value, bool use_shader);

};

#endif
