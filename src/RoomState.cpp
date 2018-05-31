
#include "RoomState.hpp"
#include "HomeState.hpp"
#include "DrawAnalyzer.hpp"
#include <cstdlib>
#include <algorithm>
#include <iostream>

RoomState::RoomState() {}

RoomState::RoomState(int index, int rooms_left) :
_stage_index(index), _rooms_left(rooms_left) 
{
    //_monsters.reserve(10); // TODO actual fix

    _elements_available = {
        Elements::Fire,
        Elements::Water,
        Elements::Earth,
        Elements::Wind,
        Elements::Electric,
    };
}

void RoomState::enter() {

    Application::window.setDrawEnabled(true);

    // Bakground image
    newGameObject()
        .loadTexture("olohuone.png");

    std::cout << "Stage index: "<< _stage_index << std::endl;
    int monster_amount = std::max(rand() % Application::stage_data[_stage_index].difficulty+1,1);
    std::cout << "Number of monsters: "<< monster_amount << std::endl;
    sf::Vector2f pos = sf::Vector2f(250,300);
    for(int i = 0; i < monster_amount; ++i)
    {
        int which_monster = rand() % Monster::Type::Player;
        Monster::Type type = static_cast<Monster::Type>(which_monster);

        auto& mon = newGameObject<Monster>(type);
        mon.setPosition(pos.x+100*i,pos.y);
        mon.health_bar.setPosition(pos.x+100*i,pos.y-20);
    }

    sf::Vector2f pos2 = sf::Vector2f(100,250);

    // Player object
    auto& plr = newGameObject<Monster>(Monster::Type::Player);
    plr.setPosition(pos2.x,pos2.y);
    plr.health_bar.setPosition(pos2.x,pos2.y-20);
}

void RoomState::update() {

    auto& monsters = getGameObjects<Monster>();
    if (monsters.size() == 1 && monsters.back().type == Monster::Type::Player) {
        if (!_rooms_left) {
            Application::stage_data[_stage_index].cleared = true;
            Application::states.changeState(HomeState());
        }
        else {
            Application::states.changeState(RoomState(_stage_index, --_rooms_left));
        }
    }

    spellCycle();
    monsterCycle();
    State::update();
}

void RoomState::exit() {
    Application::window.setDrawEnabled(false);
}

void RoomState::monsterCycle() {
    auto& monsters = getGameObjects<Monster>();
    auto it = monsters.begin();

    while (it != monsters.end()) {

        if (it->vulnerable && it->health <= 0) {
            it->die();
        }
        if (it->destroyed) {
            monsters.erase(it);
            continue;
        }

        Application::window.draw(*it);
        if(it->health < it->max_health)
        {
            Application::window.draw(it->health_bar);
            sf::RectangleShape shape = it->health_bar;
            shape.setFillColor(sf::Color::Green);
            shape.setSize(sf::Vector2f(it->health/it->max_health*shape.getSize().x,shape.getSize().y));
            Application::window.draw(shape);
        }
        it->doAction(it->behavior, monsters);
        ++it;
    }

    State::update();
}

void RoomState::spellCycle() {

    auto drawn = Application::window.getDrawnShape();
    if (drawn != DrawAnalyzer::Shape::None) {
        auto elem = determineElement(drawn);
        if (elem.type != Element::Type::None) {
            stackElement(elem);
        }
    }

    for (auto& rune : getGameObjects<Rune>()) {
        Application::window.draw(rune);
    }
}

Element RoomState::determineElement(DrawAnalyzer::Shape shape) {
    for (auto& element : _elements_available) {
        if (shape == element.shape) {
            return element;
        }
    }
    return { Element::Type::None };
}

void RoomState::stackElement(Element element) {
    float rune_spacing = 40.f;
    auto& runes = getGameObjects<Rune>();

    for (auto& rune : runes) {
        rune.addEffect(Effect::Move(rune, {rune_spacing / -2, 0}, Effect::FastIn));
    }

    auto& rune = newGameObject<Rune>(element);
    rune.loadTexture(rune.element.rune_texname, true)
        .scale(0.5)
        .align(GameObject::Alignment::Both)
        .addEffect(Effect::Fade(Effect::FastIn));

    float dx = (runes.size()-1) * rune_spacing * 0.5, dy = -150;
    Effect move_eff = Effect::Move(rune, {dx,dy}, Effect::FastIn);
    move_eff.duration = 0.7f;
    rune.addEffect(move_eff);

}
