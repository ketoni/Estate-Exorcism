
#include "HomeState.hpp"
#include "Application.hpp"
#include "StartState.hpp"
#include "SpellbookState.hpp"
#include "NotebookState.hpp"
#include "RoomState.hpp"

void HomeState::enter() {

    // background
    newGameObj().loadTexture("homeroom.png");

    // spellbook
    newGameObj().setPosition(315,130)
                .onClick([=](auto args) {
                    Application::states.overlayState(SpellbookState());
                });

    // monster manual
    newGameObj().setPosition(400,200)
                .onClick([=](auto args) {
                    Application::states.overlayState(NotebookState());
                });

    // letters
    newGameObj().setPosition(150,270)
                .onClick([=](auto args) {
                    Application::states.changeState(RoomState(0));
                });

}

void HomeState::resume() {
    auto& start_state = Application::states.accessState<StartState>();
    if (start_state.quit) {
        terminate();
    }
}
