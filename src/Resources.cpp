
#include "Resources.hpp"

Resources::Resources() :
_texture_path("tex/"), _font_path("font/"), _shader_path("shader/")
, _sound_path("sound/"), _music_path("music/")  {}

sf::Texture const& Resources::getTexture(const std::string& filename) {
    if (_textures.find(filename) == _textures.end()) {
        _textures[filename].loadFromFile(_texture_path + filename);
    }
    return _textures.at(filename);
}

sf::Font const& Resources::getFont(const std::string& filename) {
    if (_fonts.find(filename) == _fonts.end()) {
        _fonts[filename].loadFromFile(_font_path + filename);
    }
    return _fonts.at(filename);
}

sf::Sound const& Resources::getSound(const std::string& filename) {
    if (_sounds.find(filename) == _sounds.end()) {
        _sound_buffers[filename].loadFromFile(_sound_path + filename);
        _sounds[filename].setBuffer(_sound_buffers[filename]);
    }
    return _sounds.at(filename);
}

sf::Music const& Resources::getMusic(const std::string& filename) {
    if (_songs.find(filename) == _songs.end()) {
        _songs[filename].openFromFile(_music_path + filename);
    }
    return _songs.at(filename);
}

sf::Image const& Resources::getImage(const std::string& filename) {
    if (_images.find(filename) == _images.end()) {
        _images[filename].loadFromFile(_texture_path + filename);
    }
    return _images.at(filename);
}

sf::Shader* Resources::allocateShader(const std::string& filename, sf::Shader::Type type) {
    sf::Shader* ptr = new sf::Shader;
    ptr->loadFromFile(_shader_path + filename, type);
    return ptr;
}
