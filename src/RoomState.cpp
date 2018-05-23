
#include "RoomState.hpp"
#include "Application.hpp"
#include "HomeState.hpp"

RoomState::RoomState() : RoomState(0) {}

RoomState::RoomState(unsigned num_rooms) :
_rooms_left(num_rooms), _num_monsters(0) {}

void RoomState::enter() {

    // Bakground image
    newGameObj().loadTexture("olohuone.png");

    // Create a test monster
    auto& mons = newGameObj();
    _num_monsters++; 
    mons.loadTexture("tulimonsu.png")
        .setHealth(10)
        .setPosition(350,300)
        .onClick([&](auto args) { mons.health -= 3; })
        .onDeath([&]() { mons.destroyed = true; --_num_monsters; });  

}

void RoomState::update() {

    if (!_num_monsters) {
        if (!_rooms_left) {
            Application::states.changeState(HomeState());
        }
        else {
            Application::states.changeState(RoomState(--_rooms_left));
        }
    }

    auto& objs = getGameObjects();
    auto it = objs.begin();
    while (it != objs.end()) {
        if (it->vulnerable && it->health <= 0) {
            it->die();
        }
        if (it->destroyed) {
            objs.erase(it);
            continue;
        }
        it++;
    }
}

