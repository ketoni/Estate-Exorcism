
#include "RoomState.hpp"
#include "HomeState.hpp"
#include <cstdlib>
#include <algorithm>
#include <iostream>

RoomState::RoomState() {}

RoomState::RoomState(int index, int rooms_left) :
_stage_index(index), _rooms_left(rooms_left), _extra(Extra::Ready)
{
    _monsters.reserve(10); // TODO actual fix
}

void RoomState::enter() {

    // Bakground image
    newGameObj().loadTexture("olohuone.png");
    std::cout << "Stage index: "<< _stage_index << std::endl;
    int monster_amount = std::max(rand() % Application::stage_data[_stage_index].difficulty+1,1);
    std::cout << "Number of monsters: "<< monster_amount << std::endl;
    for(int i = 0; i < monster_amount; ++i)
    {
        int which_monster = rand() % Monster::Type::Player;
        Monster::Type type = static_cast<Monster::Type>(which_monster);
        auto& monster = newMonster(type);
        monster.setPosition(250+50*i,250-50*i);
        std::cout << "Monster of type "<< which_monster << std::endl;
    }


    // Player object
    newMonster(Monster::Type::Player)
    //.base()
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
}

void RoomState::update() {

    if (_monsters.size() == 1 && _monsters.back().type == Monster::Type::Player) {
        if (!_rooms_left) {
            Application::stage_data[_stage_index].cleared = true;
            Application::states.changeState(HomeState());
        }
        else {
            Application::states.changeState(RoomState(_stage_index, --_rooms_left));
        }
    }

    auto it = _monsters.begin();
    while (it != _monsters.end()) {
        if (it->vulnerable && it->health <= 0) {
            it->die();
        }
        if (it->destroyed) {
            _monsters.erase(it);
            continue;
        }
        for (auto& eff : it->effects) {
            eff.update(*it);
        }
        it++;
    }

    State::update();
}

bool RoomState::hasExtra() {
    if (_monsters.size() && _extra != Extra::End) {
        if (_extra == Extra::Ready) {
            _extra_it = _monsters.begin();
        }
        return true;
    }
    _extra = Extra::Ready;
    return false;
}

GameObject& RoomState::getExtra() {
    auto& ret = *_extra_it++;
    if (_extra_it == _monsters.end()) {
        _extra = Extra::End;
    } 
    else {
        _extra = Extra::Polling;
    }
    return ret;
}

Monster& RoomState::newMonster(Monster::Type type) {
    _monsters.emplace_back(type);
    return _monsters.back();
}
