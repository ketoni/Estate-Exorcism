#ifndef EXO_RESOURCES_HPP
#define EXO_RESOURCES_HPP

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

class Resources {

    public:
        Resources();

        sf::Texture const& getTexture(std::string const& filename);
        sf::Font const& getFont(std::string const& filename);

    private:
        std::string _texture_path;
        std::string _font_path;

        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::Font> _fonts;
};

#endif // EXO_RESOURCES_HPP
