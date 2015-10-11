#include "include/SpriteBatch.h"

SpriteBatch::SpriteBatch(){
	orthogonal_projection = glm::ortho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0); 

	//Vertex Array
	vertex_array = new Vertex[MAX_SPRITE * 4];

	//Index Array
	index_array = new GLuint[MAX_SPRITE * 6];
	
	//Sets up indices beforehand
	for (int i = 0; i < MAX_SPRITE; i++){
		int index = i*6;
		index_array[index] = i*4;
		index_array[index+1] = 1 + (i*4);
		index_array[index+2] = 2 + (i*4);

		index_array[index+3] = 0 + (i*4);
		index_array[index+4] = 2 + (i*4);
		index_array[index+5] = 3 + (i*4);
	}

    GLuint array;
    glGenVertexArrays(1, &array);
    glBindVertexArray(array);

    //generate dynamic vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, MAX_SPRITE * sizeof(Vertex), NULL, GL_STREAM_DRAW);
    
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*MAX_SPRITE*6, index_array, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
	
	vao = array;
	dynamic_vbo = vbo;
	ebo = EBO;

	next = 0;
}

void SpriteBatch::draw(Texture texture, float x, float y, float width, float height){
	if(texture.ID != current_texture.ID || next >= MAX_SPRITE){
		flush(current_texture);
		current_texture = texture;
	}
	else{
		current_texture = texture;
		add_vertices(&Vertex(x, y, 1.0, 0.0, 1.0));
		add_vertices(&Vertex(x + width, y, 1.0, 1.0, 1.0));
		add_vertices(&Vertex(x + width, y + height, 1.0, 1.0, 0.0));
		add_vertices(&Vertex(x, y + height, 1.0, 0.0, 0.0));
	}
}

void SpriteBatch::set_shader(ShaderProgram prog){
	program = prog;
}

void SpriteBatch::end(){	
	flush(current_texture);
}

void SpriteBatch::add_vertices(Vertex* v){
	vertex_array[next] = *v;
	next++;
}

void SpriteBatch::flush(Texture texture){
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, dynamic_vbo);
	glBufferData(GL_ARRAY_BUFFER, next * sizeof(Vertex), vertex_array, GL_STREAM_DRAW);
	program.set_mat4("proj", orthogonal_projection, true);
	texture.bind();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, next*6, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, next);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	next = 0;
}