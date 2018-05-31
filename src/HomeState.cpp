
#include "HomeState.hpp"
#include "Application.hpp"
#include "StartState.hpp"
#include "SpellbookState.hpp"
#include "NotebookState.hpp"
#include "LetterState.hpp"

void HomeState::enter() {

    // background
    newGameObject()
        .loadTexture("homeroom_noasset.png");

    // spellbook
    newGameObject()
        .loadTexture("lecter.png", true)
        .setPosition(327,185)
        .onClick([=](auto args) {
            Application::states.overlayState(SpellbookState());
        });

    // monster manual
    newGameObject()
        .loadTexture("monstermanual.png", true)
        .setPosition(290,290)
        .onClick([=](auto args) {
            Application::states.overlayState(NotebookState());
        });

    // letters
    newGameObject()
        .loadTexture("letters.png", true)
        .setPosition(215,295)
        .onClick([=](auto args) {
            Application::states.overlayState(LetterState());
        });

}

void HomeState::resume() {
    auto& start_state = Application::states.accessState<StartState>();
    if (start_state.quit) {
        terminate();
    }
}
