#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include "glad.h"
#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"
const int MAX_SPRITE = 2048;

struct sprite_info{
    Texture texture;
    glm::vec3 position;
    glm::vec2 size;
};

class SpriteBatch{
    private:
        GLuint dynamic_vbo;
        GLuint vao;
		GLuint ebo;
		glm::mat4 orthogonal_projection;

		Vertex* vertex_array;
		GLuint* index_array;
		int next;

        ShaderProgram program;
		Texture current_texture;
       
	public:
        SpriteBatch(int width, int height);
		~SpriteBatch();
        void begin();
        void set_shader(ShaderProgram program);
		void add_vertices(Vertex* v);
        void draw(Texture texture, float x, float y, float width, float height);
		void draw(Sprite& sprite);
		void draw(Animation& animation);
		void flush(Texture texture);
        void end();
        
};

#endif
