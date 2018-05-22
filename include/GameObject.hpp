#ifndef EXO_GAME_OBJECT_HPP
#define EXO_GAME_OBJECT_HPP

#include <functional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GameObject {

    public:
        GameObject();

        // public types
        enum Alignment {
            Horizontal,
            Vertical,
            Both,
        };

        // chained untility functions
        GameObject& loadTexture(std::string const& filepath, bool centered = false);
        GameObject& centerOrigin(bool b);
        GameObject& setPosition(float x, float y);
        GameObject& onClick(std::function<void(sf::Event::MouseButtonEvent)> call);
        GameObject& align(Alignment alignment);

        // members
        std::function<void(sf::Event::MouseButtonEvent)> click;
        sf::Sprite sprite;
        sf::Text text;

};

#endif // EXO_GAME_OBJECT_HPP
