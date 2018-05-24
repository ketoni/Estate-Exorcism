
#include "Monster.hpp"

Monster::Monster(GameObject& base, Type type) :
_base_obj(base) {

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
    }

    g.loadTexture(texname);
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
