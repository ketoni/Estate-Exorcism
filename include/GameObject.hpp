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

        void clicked(sf::Event::MouseButtonEvent event) const;
        void die() const;

        // chained untility functions
        GameObject& loadTexture(std::string const& filepath, bool centered = false);
        GameObject& centerOrigin(bool b);
        GameObject& setPosition(float x, float y);
        GameObject& scale(float factor);
        GameObject& onClick(std::function<void(sf::Event::MouseButtonEvent)> call);
        GameObject& onDeath(std::function<void()> call);
        GameObject& destroyOnDeath();
        GameObject& align(Alignment alignment);
        GameObject& setHealth(int health);
        GameObject& setVulnerable(bool b);

        // members
        sf::Sprite sprite;
        sf::Text text;

        int health;
        bool vulnerable;
        bool destroyed;

        std::vector<std::function<void(sf::Event::MouseButtonEvent)>> click_callbacks;
        std::vector<std::function<void()>> death_callbacks;
};

#endif // EXO_GAME_OBJECT_HPP
