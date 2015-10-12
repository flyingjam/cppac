#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "Vertex.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

struct TextureQuad{
	float x, y, width, height;
};

class Sprite{

	public:
		Sprite(Texture texture, int top, int left, int width, int height, float x, float y);		
		~Sprite();
		Texture texture;	
		Vertex* vertices;
		void set_position(float x, float y);
		void set_texture_coords(float top, float left, float width, float height);
		void rotate_flat(float pheta){
			glm::mat4 model;			
			model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0));
			model = glm::rotate(model, pheta, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0));
		}

	private:	
		glm::vec4 position;
		float top, left, width, height;
		void updated_vertices();
};

class Animation{	

	public:
		Animation(Texture texture, int top, int left, int width, int height, float x, float y);
		Sprite sprite;
		void add_frame(int top, int left, int width, int height);
		void update(double dt);
		void set_updates_per_second(float number);
		void set_position(float x, float y);
		void set_grid(int width, int height);
		void add_grid_frame(int column, int begin, int end);

	private:
		int current_frame;
		int grid_width, grid_height;
		double time_per_frame;
		double accumulator;
		std::vector<TextureQuad> frames;
		void set_frame(TextureQuad quad);
		
};

#endif