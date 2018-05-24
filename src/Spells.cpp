
#include "Spells.hpp"
#include "Monster.hpp"

/*
Spell::Spell(Type type, Target target, Element element, float strength, sf::Color color) :
type(type), target(target), element(element), strength(strength) {}
*/

void Spell::castOn(Monster& mon) const {
    mon.reactTo(*this);
}

void Spell::castOn(std::vector<Monster>& mons, bool target_all) const {
    for (auto& mon : mons) {
        if (target_all || mon.type != Monster::Type::Player) {
            castOn(mon);
        }
    }
}
