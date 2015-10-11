#include "include/ShaderProgram.h"

ShaderProgram::ShaderProgram(){

}

ShaderProgram::ShaderProgram(const std::string& vertex, const std::string& fragment){
    set_program(vertex, fragment);
}

ShaderProgram& ShaderProgram::Use(){
    glUseProgram(this->ID);
    return *this;
}

std::string ShaderProgram::read_shader(const std::string& filename){ 
        std::ifstream in(filename);
        if (in.is_open()){
            std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
            return content;
        }
        else
            std::cout << "File Read Error.";
        return "";
}


GLuint ShaderProgram::create_shader(GLenum shader_type, std::string source){

	GLuint shader = glCreateShader(shader_type);
	const char* shader_source_ptr = source.c_str();
	const int shader_size = source.size();

	glShaderSource(shader, 1, &shader_source_ptr, &shader_size);
	glCompileShader(shader);

	int compile_result = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	if (compile_result == GL_FALSE){
		int info_log_length = 0;
           glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
           std::vector<char> shader_log(info_log_length);
           glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
           std::cout << "ERROR compiling shader: " << std::endl << &shader_log[0] << std::endl;
           return 0;
	}
        
	return shader;

}

GLuint ShaderProgram::create_program(const std::string& vertex, const std::string& fragment){
	
	//Read in and create the vertex shader
	std::string vertex_source = read_shader(vertex);
	GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source);

	//Read in and create the fragment shader
	std::string fragment_source = read_shader(fragment);
	GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source);

	//Create the program and attatch boths haders
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);

	//does magic
	glLinkProgram(shader_program);

        //delete
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

	//return
	return shader_program;
}

void ShaderProgram::set_program(const std::string& vertex, const std::string& fragment){
    ID = create_program(vertex, fragment);
}

void ShaderProgram::set_float(const std::string& name, const float value, bool use_shader){
    if(use_shader)
        Use();
	GLint location = get_uniform_location(name);
    glUniform1f(location, value);
}
void ShaderProgram::set_vec4(const std::string& name, const glm::vec4& value, bool use_shader){
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void ShaderProgram::set_mat4(const std::string& name, const glm::mat4& value, bool use_shader){
    if(use_shader)
        this->Use();
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(value));
}

GLint ShaderProgram::get_uniform_location(const std::string& uniform){
	GLint location = glGetUniformLocation(this->ID, uniform.c_str());
	if (location < 0){
		std::cout << "FUCK";
	}
    return location;
}


