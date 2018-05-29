
#include "Window.hpp"

Window::Window(sf::VideoMode&& mode, std::string const& title) :
sf::RenderWindow(mode, title),
_drawn_shape(DrawAnalyzer::Shape::None), _draw_limit(3), _draw_enabled(false)
{
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

void Window::handleGameEvents(GameObject const& object) {
    for (auto& event : _events) {

        if (event.type == sf::Event::MouseButtonPressed) {
            handleGameEvent(object, event.mouseButton);
        }
        else if (event.type == sf::Event::KeyPressed) {
            handleGameEvent(object, event.key);
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
        eff.update(object);
        auto shader = eff.getShader();
        if (shader) {
            sf::RenderWindow::draw(object.sprite, shader);
        }
    }
    if (object.text.getString() != "") {
        sf::RenderWindow::draw(object.text);
    }
}

void Window::update() {

    if (_draw_enabled && _draw_analyzer.isCapturing() && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (_draw_timer.getElapsedTime().asSeconds() > _draw_limit) {
            _drawn_shape = _draw_analyzer.finishCapture();
        }
        else {
            auto cursor_pos = mapPixelToCoords(sf::Mouse::getPosition(*this));
            _draw_analyzer.capturePoint(cursor_pos);
            draw(_draw_analyzer.getCapture());
        }
    }

    for (auto& event : _events) {
        if (event.type == sf::Event::Closed) {
            close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (_draw_enabled && event.mouseButton.button == sf::Mouse::Right) {
                _draw_analyzer.startCapture();
                _draw_timer.restart();
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (_draw_enabled && event.mouseButton.button == sf::Mouse::Right) {
                _drawn_shape = _draw_analyzer.finishCapture();
            }
        }
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

void Window::setDrawEnabled(bool b) {
    _draw_enabled = b;
}

DrawAnalyzer::Shape Window::getDrawnShape() {
    if (_draw_analyzer.isCapturing()) {
        return DrawAnalyzer::Shape::None;
    }
    auto ret = _drawn_shape;
    _drawn_shape = DrawAnalyzer::Shape::None;
    return ret;
}
