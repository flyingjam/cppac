#include "include/SpriteBatch.h"

SpriteBatch::SpriteBatch(){
   
    GLuint array;
    glGenVertexArrays(1, &array);
    glBindVertexArray(array);

    vao = array;
    //generate dynamic vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STREAM_DRAW);
    
    dynamic_vbo = vbo;
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteBatch::draw(Texture texture, float x, float y, float width, float height){
    sprite_info sprite;
    sprite.texture = texture;
    sprite.position = glm::vec3(x, y, 1.0);
    sprite.size = glm::vec2(width, height);
    sprites.push_back(sprite);
}

Vertex[] SpriteBatch::create_vertices(glm::vec3 position, glm::vec2 size){
   Vertex vertices[] ={
        Vertex(position.x, position.y, 1.0, 0.0, 1.0),
        Vertex(position.x + size.x, position.y, 1.0, 1.0, 1.0),
        Vertex(position.x - size.x, position.y - size.y, 1.0, 1.0, 0.0),
        Vertex(position.x - size.x, position.y - size.y, 1.0, 1.0, 0.0),
        Vertex(position.x, position.y, 1.0, 0.0, 1.0),
        Vertex(position.x, position.y - size.y, 1.0, 0.0, 0.0) 
   };
   return vertices[];
}


void SpriteBatch::end(){
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, dynamic_vbo);
    //glBufferData(GL_ARRAY_BUFFER, sprites.size * sizeof(Vertex), 
}
