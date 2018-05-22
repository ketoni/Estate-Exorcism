
#include "HomeState.hpp"
#include "Application.hpp"
#include "StartState.hpp"

void HomeState::enter() {

    // background
    newGameObj().loadTexture("homeroom.png");
}

void HomeState::resume() {
    auto& start_state = Application::states.accessState<StartState>();
    if (start_state.quit) {
        terminate();
    }
}
