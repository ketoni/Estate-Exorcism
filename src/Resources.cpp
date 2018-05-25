
#include "Resources.hpp"

Resources::Resources() :
_texture_path("tex/"), _font_path("font/"), _shader_path("shader/")
, _sound_path("sound/"), _music_path("music/")  {}

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

sf::Sound& Resources::getSound(std::string const& filename) {
    if (_sounds.find(filename) == _sounds.end()) {
        _sound_buffers[filename].loadFromFile(_sound_path + filename);
        _sounds[filename].setBuffer(_sound_buffers[filename]);
    }
    return _sounds.at(filename);
}

sf::Music& Resources::getMusic(std::string const& filename) {
    if (_songs.find(filename) == _songs.end()) {
        _songs[filename].openFromFile(_music_path + filename);
    }
    return _songs.at(filename);
}

sf::Shader* Resources::allocateShader(std::string const& filename, sf::Shader::Type type) {
    sf::Shader* ptr = new sf::Shader;
    ptr->loadFromFile(_shader_path + filename, type);
    return ptr;
}
