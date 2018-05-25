#ifndef EXO_GAME_OBJECT_HPP
#define EXO_GAME_OBJECT_HPP

#include <functional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Effect.hpp"

class GameObject {

    public:
        GameObject();

        // public types
        enum Alignment {
            Horizontal,
            Vertical,
            Both,
        };

        void clicked(sf::Event::MouseButtonEvent event) const;

        // chained untility functions
        GameObject& loadTexture(std::string const& filepath, bool centered = false);
        GameObject& centerOrigin(bool b);
        GameObject& setPosition(float x, float y);
        GameObject& scale(float factor);
        GameObject& onClick(std::function<void(sf::Event::MouseButtonEvent)> call);
        GameObject& onKeystroke(std::function<void(sf::Event::KeyEvent)> call);
        GameObject& align(Alignment alignment);

        // members
        sf::Sprite sprite;
        sf::Text text;

        bool destroyed;

        std::vector<std::function<void(sf::Event::MouseButtonEvent)>> click_callbacks;
        std::vector<std::function<void(sf::Event::KeyEvent)>> keystroke_callbacks;
        std::vector<Effect> effects;
};

#endif // EXO_GAME_OBJECT_HPP
