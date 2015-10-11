#ifndef VERTEX_H
#define VERTEX_H

#include "glad.h"

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
        Position position;
        TexCoords texture;

        Vertex(float x, float y, float z, float tx, float ty);
        Vertex(float x, float y, float z);
        Vertex(float x, float y);
		Vertex();
};

#endif
