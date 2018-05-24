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
        };

        Monster(GameObject& base, Type type);

        GameObject& base();
        void die();

        // GameObject& onDeath(std::function<void()> call);
        // GameObject& destroyOnDeath();
        // GameObject& setHealth(int health);
        // GameObject& setVulnerable(bool b);

        std::vector<std::function<void()>> death_callbacks;

        Element element;

        int health;
        int max_health;
        bool vulnerable;

    private:
        std::reference_wrapper<GameObject> _base_obj;
};

#endif // EXO_MONSTER_HPP
