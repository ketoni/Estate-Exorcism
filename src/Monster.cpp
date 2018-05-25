
#include "Monster.hpp"
#include <iostream>

Monster::Monster(GameObject& base, Type type) :
type(type), health(5), max_health(5), vulnerable(true), _base_obj(base) {

    GameObject& g = Monster::base();
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

    g.loadTexture(texname);
    death_callbacks.push_back([&]() {
        g.destroyed = true;
    });
}

GameObject& Monster::base() {
    return _base_obj.get();
}

void Monster::die() {
    vulnerable = false;
    for (auto callback : death_callbacks) {
        callback();
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
    addEffect(Effect::Flash(base(), spell.color, Effect::FastPulse));
}

void Monster::addEffect(const Effect& eff) {
    base().effects.push_back(eff);
}

/*
GameObject& GameObject::onDeath(std::function<void()> call) {
    death_callbacks.push_back(call);
    return *this;
}

GameObject& GameObject::destroyOnDeath() {
    onDeath([=]() { destroyed = true; });
    return *this;
}

GameObject& GameObject::setHealth(int h) {
    health = h;
    max_health = h;
    vulnerable = true;
    return *this;
}

GameObject& GameObject::setVulnerable(bool b) {
    vulnerable = b;
    return *this;
}
*/
