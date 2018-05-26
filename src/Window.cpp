
#include "Window.hpp"


Window::Window(sf::VideoMode&& mode, std::string const& title) :
sf::RenderWindow(mode, title) {
    sf::View view;
    view.setSize(480,380);
    view.setCenter(480/2,380/2);
    setView(view);
}

void Window::pollEvents() {
    _events.clear();
    sf::Event event;
    while (pollEvent(event)) {
        _events.push_back(event);
    }
}

void Window::handleEvents(GameObject const& object) {
    for (auto& event : _events) {

        // Game-related events
        if (event.type == sf::Event::MouseButtonPressed) {
            handleGameEvent(object, event.mouseButton);
        }
        else if (event.type == sf::Event::KeyPressed) {
            handleGameEvent(object, event.key);
        }

        //  Window-only events
        if (event.type == sf::Event::Closed) {
            close();
        }
    }
}

void Window::draw(const sf::Drawable& drawable){
    sf::RenderWindow::draw(drawable);
}

void Window::draw(GameObject& object) {
    if (object.effects.empty()) {
        sf::RenderWindow::draw(object.sprite);
    }
    for (auto& eff : object.effects) {
        auto shader = eff.getShader();
        if (shader) {
            sf::RenderWindow::draw(object.sprite, shader);
        }
    }
    if (object.text.getString() != "") {
        sf::RenderWindow::draw(object.text);
    }
}

void Window::handleGameEvent(GameObject const& object, sf::Event::MouseButtonEvent event) {
    if (object.sprite.getGlobalBounds().contains(mapPixelToCoords({event.x, event.y}))) {
        object.clicked(event);
    }
}

void Window::handleGameEvent(GameObject const& object, sf::Event::KeyEvent event) {
    for (auto callback : object.keystroke_callbacks) {
        callback(event);
    }
}
