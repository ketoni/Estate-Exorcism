
#include "Window.hpp"


Window::Window(sf::VideoMode&& mode, std::string const& title) :
sf::RenderWindow(mode, title) {
    sf::View view;
    view.setSize(480,380);
    view.setCenter(480/2,380/2);
    setView(view);
}

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
    auto click_pos = mapPixelToCoords({event.x, event.y});
    for (auto const& object : objects) {
        if (object.click && object.sprite.getGlobalBounds().contains(click_pos)) {
            object.click(event);
        }
    }
}
