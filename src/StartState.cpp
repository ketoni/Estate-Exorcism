
#include "StartState.hpp"
#include "Application.hpp"

void StartState::enter() {

    // start button
    newGameObj().loadTexture("button1.png", true)
                .setPosition(0,150)
                .align(GameObject::Alignment::Horizontal)
                .setText("Start Game")
                .onClick([=](auto args) {
                    terminate();
                });

    // exit button
    newGameObj().loadTexture("button2.png", true)
                .setPosition(0,210)
                .align(GameObject::Alignment::Horizontal)
                .setText("Quit")
                .onClick([=](auto args) {
                    quit = true;
                    terminate();
                });

}
