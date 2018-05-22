
#include "Resources.hpp"

Resources::Resources() :
_texture_path("tex/"), _textures() {}

sf::Texture const& Resources::getTexture(std::string const& filename) {
    if (_textures.find(filename) == _textures.end()) {
        _textures[filename].loadFromFile(_texture_path + filename);
    }
    return _textures.at(filename);
}
