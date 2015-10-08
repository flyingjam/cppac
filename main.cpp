#include <iostream>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "include/ShaderProgram.h"
#include "include/Texture.h"

struct Position{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct TexCoords{
    GLfloat x;
    GLfloat y;
};

class Vertex{
    public:
        Vertex(float x, float y, float z, float tx, float ty);
        Vertex(float x, float y);
       Position pos;
       TexCoords tex;       
};

Vertex::Vertex(float x, float y){
    pos.x = x;
    pos.y = y;
    pos.z = 1.f;

    tex.x = 1.f;
    tex.y = 1.f;
}

Vertex::Vertex(float x, float y, float z, float tx, float ty){
    pos.x = x;
    pos.y = y;
    pos.z = z;
    tex.x = tx;
    tex.y = ty;
}

int main(){
    sf::Window window(sf::VideoMode(800, 600), "OpenGL");
    glewInit();
    /*
    GLfloat vertices[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    */ 

    Vertex vertices[] = {
        Vertex(-0.5, -0.5, 1.0, 1.0, 1.0),
        Vertex(0.5, -0.5, 1.0, 1.0, 0.0),
        Vertex(0.0, 0.5, 1.0, 0.0, 0.0)
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    ShaderProgram program("vertex.glsl", "fragment.glsl");
    program.Use();

    Texture tex("man.png");

    while (true){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                return 0;
        }

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    tex.bind();
    program.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    window.display();
    }
    return 0;
}
