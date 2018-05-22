
#include "Application.hpp"
#include "StartState.hpp"
#include "HomeState.hpp"

Resources Application::resources;
Application::Context Application::context;
StateEngine Application::states;

Application::Application() :
_window({960,760}, "Estate Exorcism") {
   _window.setFramerateLimit(60);
   context.window_size = _window.getSize();
   context.view_size = _window.getView().getSize();

   states.changeState(HomeState());
   states.overlayState(StartState());
}

void Application::run() {

    while (states.update() && _window.isOpen()) {
        _window.clear();
        states.drawAll(_window);
        _window.display();
        _window.handleEvents(states.getUIObjects());
    }

    states.flush();
    _window.close();
}
