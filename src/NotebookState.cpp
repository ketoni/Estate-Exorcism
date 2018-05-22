
#include "NotebookState.hpp"

void NotebookState::enter() {

    // Notebook sprite
    newGameObj().loadTexture("notebook.png")
                .centerOrigin(true)
                .align(GameObject::Alignment::Both);

    // Exit button
    newGameObj().setPosition(400,300)
                .click = [=](auto args) {
                    terminate();
                };
}
