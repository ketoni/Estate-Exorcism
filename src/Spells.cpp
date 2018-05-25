
#include "Spells.hpp"
#include "Monster.hpp"

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
