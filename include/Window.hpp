#ifndef EXO_WINDOW_HPP
#define EXO_WINDOW_HPP

#include <vector>
#include "GameObject.hpp"

class Window : public sf::RenderWindow {

    public:
        Window(sf::VideoMode&& mode, std::string const& title);

        void pollEvents();
        void handleEvents(GameObject const& objects);
        void draw(const sf::Drawable& drawable);
        void draw(GameObject& object);

        void handleGameEvent(GameObject const& object, sf::Event::MouseButtonEvent event);
        void handleGameEvent(GameObject const& object, sf::Event::KeyEvent event);

    private:
        std::vector<sf::Event> _events;
};

#endif // EXO_WINDOW_HPP
