
#include "Window.hpp"


Window::Window(sf::VideoMode&& mode, std::string const& title) :
sf::RenderWindow(mode, title) {}

void Window::handleEvents(std::vector<GameObject> const& objects) {
    sf::Event event;
    while (pollEvent(event)) {

        // Game-related events
        //
        if (event.type == sf::Event::MouseButtonPressed) {
            handleGameEvent(objects, event.mouseButton);
        }

        //  Window-only events
        //
        if (event.type == sf::Event::Closed) {
            close();
        }

    }
}

void Window::draw(GameObject& object) {
    if (object.sprite.getTexture() != nullptr) {
        sf::RenderWindow::draw(object.sprite);
    }
    if (object.text.getString() != "") {
        sf::RenderWindow::draw(object.text);
    }
}

void Window::handleGameEvent(std::vector<GameObject> const& objects, sf::Event::MouseButtonEvent event) {
    for (auto const& object : objects) {
        if (object.click && object.sprite.getGlobalBounds().contains(event.x, event.y)) {
            object.click(event);
        }
    }
}
