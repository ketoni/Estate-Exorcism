#ifndef EXO_MONSTER_HPP
#define EXO_MONSTER_HPP

#include "GameObject.hpp"
#include "Spells.hpp"

class Monster {

    public:

        enum Type {
            Lizard,
            Flying,
            Slime,
            Garden,
            Wisp,
            Player,
        };

        Monster(GameObject& base, Type type);

        GameObject& base();
        void die();
        void reactTo(const Spell& spell);
        void addEffect(const Effect& effect);

        // GameObject& onDeath(std::function<void()> call);
        // GameObject& destroyOnDeath();
        // GameObject& setHealth(int health);
        // GameObject& setVulnerable(bool b);

        std::vector<std::function<void()>> death_callbacks;

        Element element;
        Type type;

        int health;
        int max_health;
        bool vulnerable;

    private:
        std::reference_wrapper<GameObject> _base_obj;
};

#endif // EXO_MONSTER_HPP
