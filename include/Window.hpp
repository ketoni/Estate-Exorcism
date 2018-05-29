#ifndef EXO_WINDOW_HPP
#define EXO_WINDOW_HPP

#include <vector>
#include "GameObject.hpp"
#include "DrawAnalyzer.hpp"

class Window : public sf::RenderWindow {

    public:
        Window(sf::VideoMode&& mode, std::string const& title);

        void pollEvents();
        void update();

        void draw(const sf::Drawable& drawable);
        void draw(GameObject& object);

        void handleGameEvents(GameObject const& objects);
        void handleGameEvent(GameObject const& object, sf::Event::MouseButtonEvent event);
        void handleGameEvent(GameObject const& object, sf::Event::KeyEvent event);

        void setDrawEnabled(bool b);
        DrawAnalyzer::Shape getDrawnShape();

    private:
        std::vector<sf::Event> _events;

        DrawAnalyzer::Shape _drawn_shape;
        DrawAnalyzer _draw_analyzer;
        sf::Clock _draw_timer;
        float _draw_limit;
        bool _draw_enabled;
};

#endif // EXO_WINDOW_HPP
