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

        enum Behavior {
            Idle,
            AttackPlayer,
            AttackMonster,
            AttackAny,
        };

        Monster(Type type);

        void die();

        void doAction(Behavior behavior, std::vector<Monster>& others);
        void attackMonster(Monster& other);
        bool canAttack();

        void reactTo(const Spell& spell);
        void addEffect(const Effect& effect);

        std::vector<std::function<void(Monster&)>> death_callbacks;
        sf::RectangleShape health_bar;

        Element element;
        Type type;


        std::vector<Spell> spells;
        sf::Clock attack_timer;
        float attack_interval;
        Behavior behavior;
        float health;
        float max_health;
        bool vulnerable;
};

#endif // EXO_MONSTER_HPP
