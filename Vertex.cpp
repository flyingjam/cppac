#include "include/Vertex.h"

Vertex::Vertex(){
	position.x = 0.0;
	position.y = 0.0;
	position.z = 1.0;
	texture.x = 0.0;
	texture.y = 0.0;
}

Vertex::Vertex(float x, float y, float z, float tx, float ty){
    position.x = x;
    position.y = y;
    position.z = z;

    texture.x = tx;
    texture.y = ty;
}

Vertex::Vertex(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;

    texture.x = 1.0;
    texture.y = 1.0;
}

Vertex::Vertex(float x, float y){
    position.x = x;
    position.y = y;
    position.z = 1.0;

    texture.x = 1.0;
    texture.y = 1.0;
}

