#ifndef EXO_APPLICATION_HPP
#define EXO_APPLICATION_HPP

#include "Window.hpp"
#include "StateEngine.hpp"
#include "Resources.hpp"

class Application {

    public:
        Application();
        void run();

        struct Context {
            sf::Vector2u window_size;
            sf::Vector2f view_size;
        };

        static Context context;
        static Resources resources;
        static StateEngine states;

    private:
        Window _window;
};

#endif // EXO_APPLICATION_HPP
