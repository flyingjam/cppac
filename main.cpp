#include <iostream>
#include "include/glad.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "include/ShaderProgram.h"
#include "include/Texture.h"
#include "include/Vertex.h"
#include "include/ResourceManager.h"
#include "include/SpriteBatch.h"
#include "include/Sprite.h"

int main(){
    sf::Window window(sf::VideoMode(800, 600), "OpenGL");
    //glewInit();
    gladLoadGL(); 
    /*
    GLfloat vertices[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    */ 


    auto program = ResourceManager::load_shader("vertex.glsl", "fragment.glsl", "default");

	SpriteBatch batch(800, 600);
	batch.set_shader(program);
	auto tex = ResourceManager::load_texture("man.png", "man");
	auto leaf = ResourceManager::load_texture("leaf.png", "leaf");
	Animation sprite(leaf, 0, 0, 34, 50, 200.f, 200.f);
	//sprite.add_frame(34, 0, 34, 50);
	//sprite.add_frame(68, 0, 34, 50);
	//sprite.add_frame(102, 0, 34, 50);
	sprite.set_updates_per_second(5.f);
	sprite.set_grid(34, 50);
	sprite.add_grid_frame(0, 1, 3);
	Sprite test(tex, 0, 0, 30, 40, 200.f, 200.f); 
	sf::Clock clock;
	float x = 100.f;
	float y = 100.f;
	double dt = 0;
    while (true){
		sf::Time dt = clock.restart();
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                return 0;
        }

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		batch.draw(sprite);
		y = y + (30 * dt.asSeconds());
		sprite.set_position(x, y);
		sprite.update(dt.asSeconds());
		batch.end();
        window.display();
    }

	ResourceManager::clear();
    return 0;
}
