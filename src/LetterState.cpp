#include "Application.hpp"
#include "RoomState.hpp"
#include "LetterState.hpp"

void LetterState::enter() {

    // Notebook sprite
    newGameObj().loadTexture("notebook.png")
                .centerOrigin(true)
                .align(GameObject::Alignment::Both);


    for(int i = 0; i < Application::stage_data.size(); i++)
    {
        newGameObj().loadTexture("wispinapot.png")
                    .setPosition(100+100*i,100)
                    .setText(Application::stage_data[i].name)
                    .onClick([=] (auto args) {
                        Application::states.flush();
                        Application::states.changeState(RoomState(i,Application::stage_data[i].room_amount-1));
                    })
                    .sprite.setColor(sf::Color(255,255,255,255-Application::stage_data[i].cleared*155));
    }
    // Spellbook sprite


    // Exit button
    newGameObj().setPosition(400,300)
                .onClick([=](auto args) {
                    terminate();
                });
}
