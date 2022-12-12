#include "background.hpp"
#include <iostream>


// cons

Background::Background() {
    initBackground();
    backgroundPos();
}
// public functions
void Background::initBackground() {
    if(!texture.loadFromFile("D:/Coding/Project/SFML/RocketUp/Gambar/spaceBG.jpg")) {
        std::cout << "File not found" << std:: endl;
    }
    texture.setRepeated(true);
    background.setTexture(texture);
    parallaxShader.loadFromMemory(
        "uniform float offset;"

        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].y = gl_TexCoord[0].y - offset;" // magic
        "    gl_FrontColor = gl_Color;"
        "}"
        , sf::Shader::Vertex);

}

void Background::drawBackground(sf::RenderWindow &w) {
    w.draw(background, &parallaxShader);
}

void Background::backgroundPos() {
}

void Background::moveBackground() {
    parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() / 100);
}

