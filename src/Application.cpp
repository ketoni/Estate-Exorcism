
#include "Application.hpp"
#include "StartState.hpp"
#include "HomeState.hpp"

Resources Application::resources;
Application::Context Application::context;
StateEngine Application::states;
std::vector<Application::StageData> Application::stage_data;
Window Application::window({960,760}, "Estate Exorcism");

Application::Application()
{
   window.setFramerateLimit(60);
   context.window_size = window.getSize();
   context.view_size = window.getView().getSize();
   stage_data.push_back({1,1,0,"pentin peräpukama"});
   stage_data.push_back({2,2,0,"einon eräreikä"});
   states.changeState(HomeState());
   states.overlayState(StartState());
}

void Application::run() {

    while (states.update() && window.isOpen()) {
        window.display();
        window.pollEvents();
        states.handObjects(window);
        window.clear();
        states.handDrawables(window);
        window.update();
    }

    states.flush();
    window.close();
}
