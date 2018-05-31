
#include "NotebookState.hpp"

void NotebookState::enter() {

    // Notebook sprite
    newGameObject()
        .loadTexture("notebook.png", true)
        .align(GameObject::Alignment::Both);

    // Exit button
    newGameObject()
        .setPosition(400,300)
        .onClick([=](auto args) {
            terminate();
        });
}
