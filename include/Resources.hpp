#ifndef EXO_RESOURCES_HPP
#define EXO_RESOURCES_HPP

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Resources {

    public:
        Resources();

        sf::Texture const& getTexture(std::string const& filename);
        sf::Font const& getFont(std::string const& filename);
        sf::Sound& getSound(std::string const& filename);
        sf::Music& getMusic(std::string const& filename);

        sf::Shader* allocateShader(std::string const& filename, sf::Shader::Type type);

    private:
        std::string _texture_path;
        std::string _font_path;
        std::string _shader_path;
        std::string _sound_path;
        std::string _music_path;

        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::Font> _fonts;
        std::unordered_map<std::string, sf::Sound> _sounds;
        std::unordered_map<std::string, sf::SoundBuffer> _sound_buffers;
        std::unordered_map<std::string, sf::Music> _songs;
};

#endif // EXO_RESOURCES_HPP
