#include "include/SpriteBatch.h"

SpriteBatch::SpriteBatch(int width, int height){
	orthogonal_projection = glm::ortho(0.f, (float)width, (float)height, 0.f, -1.f, 1.f); 

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

		index_array[index+3] = (i*4);
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

SpriteBatch::~SpriteBatch(){
	glDeleteBuffers(1, &dynamic_vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);

	delete [] vertex_array;
	delete [] index_array;
}

void SpriteBatch::draw(Texture texture, float x, float y, float width, float height){
	if(texture.ID != current_texture.ID || next + 4>= MAX_SPRITE){
		flush(current_texture);
		current_texture = texture;
	}
	else{
		//current_texture = texture;
		add_vertices(&Vertex(x, y, 1.0, 0.0, 0.0));
		add_vertices(&Vertex(x + width, y, 1.0, 30.0, 0.0));
		add_vertices(&Vertex(x + width, y + height, 1.0, 30.0, 40.0));
		add_vertices(&Vertex(x, y + height, 1.0, 0.0, 40.0));
	}
}

void SpriteBatch::draw(Sprite& sprite){
	if(sprite.texture.ID != current_texture.ID || next + 4 >= MAX_SPRITE){
		flush(current_texture);
		current_texture = sprite.texture;
	}
	else{
		//todo memcpy the data... if I dare
		add_vertices(&sprite.vertices[0]);
		add_vertices(&sprite.vertices[1]);
		add_vertices(&sprite.vertices[2]);
		add_vertices(&sprite.vertices[3]);
	}
}

void SpriteBatch::draw(Animation& animation){
	Sprite* sprite = &animation.sprite;
	if(sprite->texture.ID != current_texture.ID || next + 4 >= MAX_SPRITE){
		flush(current_texture);
		current_texture = sprite->texture;
	}
	else{
		//todo memcpy the data... if I dare
		add_vertices(&sprite->vertices[0]);
		add_vertices(&sprite->vertices[1]);
		add_vertices(&sprite->vertices[2]);
		add_vertices(&sprite->vertices[3]);
	}
}

void SpriteBatch::set_shader(ShaderProgram prog){
	program = prog;
}

void SpriteBatch::end(){	
	flush(current_texture);
}

void SpriteBatch::add_vertices(Vertex* v){
	assert(next <= MAX_SPRITE);
	vertex_array[next] = *v;
	next++;
}

void SpriteBatch::flush(Texture texture){
	texture.bind();

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, dynamic_vbo);
	//glBufferData(GL_ARRAY_BUFFER, next * sizeof(Vertex), vertex_array, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, next * sizeof(Vertex), vertex_array);

	//create projection matrix for texture coordinates
	glm::mat4 texture_projection = glm::ortho(-1*(float)texture.width, (float)texture.width, -1*(float)texture.height, (float)texture.height, 1.f, 0.f);

	//set uniforms
	program.set_mat4("proj", orthogonal_projection, true);
	program.set_mat4("frag_proj", texture_projection, false);

	//Bind EBO and draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, next*6, GL_UNSIGNED_INT, 0);

	//unbind stuff
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	next = 0;
}