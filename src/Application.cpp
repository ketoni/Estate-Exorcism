
#include "Application.hpp"
#include "StartState.hpp"
#include "HomeState.hpp"

Resources Application::resources;
Application::Context Application::context;
StateEngine Application::states;
std::vector<Application::StageData> Application::stage_data;

Application::Application() :
_window({960,760}, "Estate Exorcism") {
   _window.setFramerateLimit(60);
   context.window_size = _window.getSize();
   context.view_size = _window.getView().getSize();
   stage_data.push_back({1,1,0,"pentin peräpukama"});
   stage_data.push_back({2,2,0,"einon eräreikä"});
   states.changeState(HomeState());
   states.overlayState(StartState());
}

void Application::run() {

    while (states.update() && _window.isOpen()) {
        _window.clear();
        states.handDrawables(_window);
        _window.display();
        _window.pollEvents();
        states.handObjects(_window);
    }

    states.flush();
    _window.close();
}
