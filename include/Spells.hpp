#ifndef EXO_SPELL_HPP
#define EXO_SPELL_HPP

#include <SFML/Graphics.hpp>

class Monster; // Forward declaration

struct Element {
    enum Type {
        Neutral,
        Fire,
        Water,
        Earth,
        Wind,
        Electric,
        None,
    };

    Type type;
    Type strong;
    Type weak;
};

namespace Elements {
    static Element Fire = { Element::Type::Fire, Element::Type::Wind, Element::Type::Water };
    static Element Water = { Element::Type::Water, Element::Type::Fire, Element::Type::Earth };
    static Element Earth = { Element::Type::Earth, Element::Type::Water, Element::Type::Electric };
    static Element Wind = { Element::Type::Wind, Element::Type::Electric, Element::Type::Fire };
    static Element Electric = { Element::Type::Electric, Element::Type::Earth, Element::Type::Wind };
    static Element Neutral = { Element::Type::Neutral, Element::Type::None, Element::Type::None };
};

struct Spell {

    enum Type {
        Offensive,
        Defensive,
        Seal,
    };

    Type type;
    Element element;
    float strength;
    sf::Color color;

    void castOn(Monster& mon) const;
    void castOn(std::vector<Monster>&, bool target_all = false) const;

};

namespace Spells {
    static Spell Fire = { Spell::Type::Offensive, Elements::Fire, 1, sf::Color::Red };
    static Spell Water = { Spell::Type::Offensive, Elements::Water, 1, sf::Color::Cyan };
    static Spell Earth = { Spell::Type::Offensive, Elements::Earth, 1, sf::Color::Green };
    static Spell Wind = { Spell::Type::Offensive, Elements::Wind, 1, sf::Color::White };
    static Spell Electric = { Spell::Type::Offensive, Elements::Electric, 1, sf::Color::Yellow };
}

#endif // EXO_SPELL_HPP
