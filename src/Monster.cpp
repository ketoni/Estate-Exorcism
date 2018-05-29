
#include "Monster.hpp"
#include <iostream>
#include <math.h>

Monster::Monster(Type type) :
type(type), health(5), max_health(5), vulnerable(true) {

    behavior = Behavior::AttackPlayer;
    attack_interval = 2.5f + fmod(std::rand(), 2.f) + fmod(std::rand(), 0.5f);
    death_callbacks.push_back([](Monster& thiz) {
        thiz.destroyed = true;
    });

    std::string texname;
    switch (type) {
        case Lizard:
            texname = "tulimonsu.png";
            element = Elements::Fire;
            spells = { Spells::Fire };
            break;
        case Flying:
            texname = "liilahirvio.png";
            element = Elements::Wind;
            spells = { Spells::Wind };
            break;
        case Slime:
            texname = "slimu.png";
            element = Elements::Water;
            spells = { Spells::Water };
            break;
        case Garden:
            texname = "gardener.png";
            element = Elements::Earth;
            spells = { Spells::Earth };
            break;
        case Wisp:
            texname = "wispinapot.png";
            element = Elements::Electric;
            spells = { Spells::Electric };
            break;
        case Player:
            texname = "exomage.png";
            element = Elements::Neutral;
            behavior = Behavior::Idle;
    }
    //std::cout << "KOKOA ON "<<  sprite.getLocalBounds().width << std::endl;
    loadTexture(texname);
    health_bar = sf::RectangleShape(sf::Vector2f(sprite.getTexture()->getSize().x,8));
    health_bar.setFillColor(sf::Color(255,0,0,255));

    death_callbacks.push_back([](Monster& thiz) {
        thiz.destroyed = true;
    });
}

void Monster::die() {
    vulnerable = false;
    for (auto callback : death_callbacks) {
        callback(*this);
    }
}

void Monster::doAction(Behavior behavior, std::vector<Monster>& others) {
    for (auto& mon : others) {
        if (mon.type == Type::Player && behavior == Behavior::AttackPlayer) {
            attackMonster(mon);
        }
        else if (mon.type != Type::Player && behavior == Behavior::AttackMonster) {
            attackMonster(mon);
        }
        else if (behavior == Behavior::AttackAny){
            attackMonster(mon);
        }
    }
}

void Monster::attackMonster(Monster& other) {
    if (canAttack()) {
        spells.at(std::rand() % (spells.size())).castOn(other);
        attack_timer.restart();
    }
}

bool Monster::canAttack() {
    return attack_timer.getElapsedTime().asSeconds() > attack_interval && spells.size();
}

void Monster::reactTo(const Spell& spell) {
    float knock = 10.f;
    if (spell.element.strong == element.type) {
        health -= spell.strength * 2.f;
        knock = 20.f;
    }
    else if (spell.element.weak == element.type) {
        health -= spell.strength * 0.5f;
        knock = 3.f;
    }
    else {
        health -= spell.strength;
    }
    std::cout << "Monster type " << (int)type << " Health: " << health << std::endl;
    addEffect(Effect::Tint(spell.element.color, Effect::FastPulse));
    addEffect(Effect::Move(*this, {knock,0}, Effect::FastPulse));
}

