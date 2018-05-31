
#include "SpellbookState.hpp"

void SpellbookState::enter() {

    // Spellbook sprite
    newGameObject()
        .loadTexture("spellbook.png", true)
        .align(GameObject::Alignment::Both);

    // Exit button
    newGameObject()
        .setPosition(400,300)
        .onClick([=](auto args) {
            terminate();
        });
}
