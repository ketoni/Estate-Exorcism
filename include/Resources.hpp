#ifndef EXO_RESOURCES_HPP
#define EXO_RESOURCES_HPP

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Resources {

    public:
        Resources();

        sf::Texture const& getTexture(const std::string& filename);
        sf::Font const& getFont(const std::string& filename);
        sf::Sound const& getSound(const std::string& filename);
        sf::Music const& getMusic(const std::string& filename);
        sf::Image const& getImage(const std::string& filename);

        sf::Shader* allocateShader(const std::string& filename, sf::Shader::Type type);

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
        std::unordered_map<std::string, sf::Image> _images;
};

#endif // EXO_RESOURCES_HPP
