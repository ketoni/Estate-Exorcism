
#include "SpellbookState.hpp"

void SpellbookState::enter() {

    // Spellbook sprite
    newGameObj().loadTexture("spellbook.png")
                .centerOrigin(true)
                .align(GameObject::Alignment::Both);

    // Exit button
    newGameObj().setPosition(400,300)
                .click = [=](auto args) {
                    terminate();
                };
}
