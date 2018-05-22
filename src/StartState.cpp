
#include "StartState.hpp"
#include "Application.hpp"

void StartState::enter() {

    // start button
    newGameObj().loadTexture("nappula.png", true)
                .setPosition(0,150)
                .align(GameObject::Alignment::Horizontal)
                .click = [=](auto args) {
                    terminate();
                };

    // exit button
    newGameObj().loadTexture("nappula.png", true)
                .setPosition(0,210)
                .align(GameObject::Alignment::Horizontal)
                .click = [=](auto args) {
                    quit = true;
                    terminate();
                };

}

