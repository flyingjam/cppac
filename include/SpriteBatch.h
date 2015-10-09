#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include "glad.h"
#include <vector>
#include <glm/glm.hpp>

const int MAX_SPRITE = 2048;

struct sprite_info{
    
};

class SpriteBatch{
    public:
        GLuint dyanmic_vbo;
        GLuint vao;

        SpriteBatch();

        void render_batch();
        
        void begin();
        void draw();
        void end();
        
};

#endif
