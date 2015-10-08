#include "include/Texture.h"

Texture::Texture(const std::string filepath){
    //generate id
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    
    //misc settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //load data
    sf::Image image;
    image.loadFromFile(filepath);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());


    glBindTexture(GL_TEXTURE_2D, 0);

    ID = id;
    width = image.getSize().x;
    height = image.getSize().y;
}

void Texture::bind() const{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const{
    glBindTexture(GL_TEXTURE_2D, 0);
}

