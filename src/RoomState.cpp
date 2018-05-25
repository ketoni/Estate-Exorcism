
#include "RoomState.hpp"
#include "Application.hpp"
#include "HomeState.hpp"

RoomState::RoomState() : RoomState(0) {}

RoomState::RoomState(unsigned num_rooms) :
_rooms_left(num_rooms) {}

void RoomState::enter() {

    // Bakground image
    newGameObj().loadTexture("olohuone.png");

    // Player object
    newMonster(Monster::Type::Player)
    .base()
    .setPosition(100,250)
    .onKeystroke([&](auto args) {
        if (args.code == sf::Keyboard::Num1) {
            Spells::Fire.castOn(_monsters);
        }
        if (args.code == sf::Keyboard::Num2) {
            Spells::Water.castOn(_monsters);
        }
        if (args.code == sf::Keyboard::Num3) {
            Spells::Earth.castOn(_monsters);
        }
        if (args.code == sf::Keyboard::Num4) {
            Spells::Wind.castOn(_monsters);
        }
        if (args.code == sf::Keyboard::Num5) {
            Spells::Electric.castOn(_monsters);
        }
    });

    // Create a test monster
    auto& mon = newMonster(Monster::Type::Slime);
    mon.base().setPosition(350,300);

}

void RoomState::update() {

    if (_monsters.empty()) {
        if (!_rooms_left) {
            Application::states.changeState(HomeState());
        }
        else {
            Application::states.changeState(RoomState(--_rooms_left));
        }
    }

    auto it = _monsters.begin();
    while (it != _monsters.end()) {
        if (it->vulnerable && it->health <= 0) {
            it->die();
        }
        if (it->base().destroyed) {
            _monsters.erase(it);
            continue;
        }
        for (auto& eff : it->base().effects) {
            eff.update();
        }
        it++;
    }

    State::update();
}

Monster& RoomState::newMonster(Monster::Type type) {
    _monsters.emplace_back(newGameObj(), type);
    return _monsters.back();
}
