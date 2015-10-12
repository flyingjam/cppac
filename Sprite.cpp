#include "include/Sprite.h"

Sprite::Sprite(Texture tex, int t, int l, int w, int h, float x, float y){
	vertices = new Vertex[4];
	texture = tex;
	position = glm::vec4(x, y, 1.0, 1.0);
	top = t;
	left = l;
	width = w;
	height = h;
	updated_vertices();
}

Sprite::~Sprite(){
	delete [] vertices;
}

void Sprite::updated_vertices(){
	vertices[0] = Vertex(position.x, position.y, position.z, top, left);
	vertices[1] = Vertex(position.x + width, position.y, position.z, top + width, left);
	vertices[2] = Vertex(position.x + width, position.y + height, position.z, top + width, left + height);
	vertices[3] = Vertex(position.x, position.y + height, position.z, top, left + height);
}

void Sprite::set_position(float x, float y){
	position.x = x;
	position.y = y;
	updated_vertices();
}

void Sprite::set_texture_coords(float t, float l, float w, float h){
	top = t;
	left = l;
	width = w;
	height = h;
	updated_vertices();
}

Animation::Animation(Texture tex, int t, int l, int w, int h, float x, float y) :
	sprite(tex, t, l, w, h, x, y){
	add_frame(t, l, w, h);
	current_frame = 0;
	accumulator = 0;
	time_per_frame = .1;
	grid_width = 0;
	grid_height = 0;
}

void Animation::set_position(float x, float y){
	sprite.set_position(x, y);
}

void Animation::add_frame(int top, int left, int width, int height){
	TextureQuad quad = {top, left, width, height};
	frames.push_back(quad);
}

void Animation::set_grid(int width, int height){
	grid_width = width;
	grid_height = height;
}

void Animation::add_grid_frame(int column, int begin, int end){
	int y = column * grid_height;
	int start_x = begin * grid_width;
	int end_x = end * grid_width;

	for(int i = start_x; i <= end_x; i += grid_width){
		add_frame(i, y, grid_width, grid_height);	
	}
}

void Animation::set_frame(TextureQuad quad){	
	sprite.set_texture_coords(quad.x, quad.y, quad.width, quad.height);
}

void Animation::set_updates_per_second(float number){
	assert(number > 0);
	time_per_frame = 1.f / number;
}

void Animation::update(double dt){
	accumulator += dt;
	while (accumulator > time_per_frame){
		current_frame = (current_frame + 1) % frames.size();
		set_frame(frames[current_frame]);
		accumulator -= time_per_frame;
	}
}