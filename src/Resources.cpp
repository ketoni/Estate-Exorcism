
#include "Resources.hpp"

Resources::Resources() :
_texture_path("tex/"), _font_path("font/"), _shader_path("shader/") {}

sf::Texture const& Resources::getTexture(std::string const& filename) {
    if (_textures.find(filename) == _textures.end()) {
        _textures[filename].loadFromFile(_texture_path + filename);
    }
    return _textures.at(filename);
}

sf::Font const& Resources::getFont(std::string const& filename) {
    if (_fonts.find(filename) == _fonts.end()) {
        _fonts[filename].loadFromFile(_texture_path + filename);
    }
    return _fonts.at(filename);
}

sf::Shader* Resources::allocateShader(std::string const& filename, sf::Shader::Type type) {
    sf::Shader* ptr = new sf::Shader;
    ptr->loadFromFile(_shader_path + filename, type);
    return ptr;
}
