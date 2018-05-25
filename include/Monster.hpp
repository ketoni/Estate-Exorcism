#ifndef EXO_MONSTER_HPP
#define EXO_MONSTER_HPP

#include "GameObject.hpp"
#include "Spells.hpp"

class Monster : public GameObject {

    public:

        enum Type {
            Lizard,
            Flying,
            Slime,
            Garden,
            Wisp,
            Player,
        };

        Monster(Type type);

        void die();
        void reactTo(const Spell& spell);
        void addEffect(const Effect& effect);

        std::vector<std::function<void(Monster&)>> death_callbacks;

        Element element;
        Type type;

        int health;
        int max_health;
        bool vulnerable;
};

#endif // EXO_MONSTER_HPP
