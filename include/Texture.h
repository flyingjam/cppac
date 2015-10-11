#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "glad.h"

class Texture{

    public:
        GLuint ID;

        int width, height;

		Texture();
		Texture(const std::string& filepath);

        void bind() const;
        void unbind() const;
        
};

#endif
