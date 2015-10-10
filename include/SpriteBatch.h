#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include "glad.h"
#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Vertex.h"

const int MAX_SPRITE = 2048;

struct sprite_info{
    Texture texture;
    glm::vec3 position;
    glm::vec2 size;
};

class SpriteBatch{
    public:
        GLuint dynamic_vbo;
        GLuint vao;

        Program program;
        SpriteBatch();
        std::vector<sprite_info> sprites;
        Vertex[] create_vertices(glm::vec3 position, glm::vec2 size);
        
        void render_batch();
        
        void begin();
        void set_shader(Program program);
        void draw(Texture texture, float x, float y, float width, float height);
        void end();
        
};

#endif
