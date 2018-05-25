
#include "Monster.hpp"
#include <iostream>

Monster::Monster(Type type) :
type(type), health(5), max_health(1), vulnerable(true) {

    std::string texname;

    switch (type) {
        case Lizard:
            texname = "tulimonsu.png";
            element = Elements::Fire;
            break;
        case Flying:
            texname = "liilahirvio.png";
            element = Elements::Wind;
            break;
        case Slime:
            texname = "slimu.png";
            element = Elements::Water;
            break;
        case Garden:
            texname = "gardener.png";
            element = Elements::Earth;
            break;
        case Wisp:
            texname = "wispinapot.png";
            element = Elements::Electric;
            break;
        case Player:
            texname = "exomage.png";
            element = Elements::Neutral;
    }

    loadTexture(texname);
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

void Monster::reactTo(const Spell& spell) {
    if (spell.element.strong == element.type) {
        health -= spell.strength * 2.f;

    }
    else if (spell.element.weak == element.type) {
        health -= spell.strength * 0.5f;
    }
    else {
        health -= spell.strength;
    }
    std::cout << "Monster type " << (int)type << " Health: " << health << std::endl;
    addEffect(Effect::Flash(spell.color, Effect::FastPulse));
}

void Monster::addEffect(const Effect& eff) {
    effects.push_back(eff);
}

