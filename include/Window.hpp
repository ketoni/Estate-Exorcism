#ifndef EXO_WINDOW_HPP
#define EXO_WINDOW_HPP

#include <vector>
#include "GameObject.hpp"

class Window : public sf::RenderWindow {

    public:
        Window(sf::VideoMode&& mode, std::string const& title);

        void handleEvents(std::vector<GameObject> const& objects);
        void draw(GameObject& object);

        void handleGameEvent(std::vector<GameObject> const& objects, sf::Event::MouseButtonEvent event);

};

#endif // EXO_WINDOW_HPP
