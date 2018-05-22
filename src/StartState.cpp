
#include "StartState.hpp"
#include "Application.hpp"

void StartState::enter() {

    // start button
    newGameObj().loadTexture("nappula.png", true)
                .setPosition(0,500)
                .align(GameObject::Alignment::Horizontal)
                .click = [=](auto args) {
                    terminate();
                };

    // exit button
    newGameObj().loadTexture("nappula.png", true)
                .setPosition(0,600)
                .align(GameObject::Alignment::Horizontal)
                .click = [=](auto args) {
                    quit = true;
                    terminate();
                };

}

