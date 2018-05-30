#ifndef EXO_SPELL_HPP
#define EXO_SPELL_HPP

#include <SFML/Graphics.hpp>
#include "DrawAnalyzer.hpp"

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

    DrawAnalyzer::Shape shape;
    std::string rune_texname;
    sf::Color color;
};

namespace Elements {
    static Element Fire = {
        Element::Type::Fire,
        Element::Type::Wind,
        Element::Type::Water,
        DrawAnalyzer::Shape::Horizontal,
        "firerune.png",
        sf::Color::Red,
    };
    static Element Water = {
        Element::Type::Water,
        Element::Type::Fire,
        Element::Type::Earth,
        DrawAnalyzer::Shape::Vertical,
        "waterrune.png",
        sf::Color::Cyan,
    };
    static Element Earth = {
        Element::Type::Earth,
        Element::Type::Water,
        Element::Type::Electric,
        DrawAnalyzer::Shape::Circle,
        "earthrune.png",
        sf::Color::Green,
    };
    static Element Wind = {
        Element::Type::Wind,
        Element::Type::Electric,
        Element::Type::Fire,
        DrawAnalyzer::Shape::VeeUp,
        "windrune.png",
        sf::Color::White,
    };
    static Element Electric = {
        Element::Type::Electric,
        Element::Type::Earth,
        Element::Type::Wind,
        DrawAnalyzer::Shape::VeeDown,
        "elecrune.png",
        sf::Color::Yellow,
    };
    static Element Neutral;
};

struct Spell {

    enum Type {
        Offensive,
        Heal,
        Defensive,
        Buff,
        Debuff,
        Seal,
    };

    Type type;
    Element element;
    float strength;

    void castOn(Monster& mon) const;
    void castOn(std::vector<Monster>&, bool target_all = false) const;

};

namespace Spells {
    static Spell Fire = { Spell::Type::Offensive, Elements::Fire, 1 };
    static Spell Water = { Spell::Type::Offensive, Elements::Water, 1 };
    static Spell Earth = { Spell::Type::Offensive, Elements::Earth, 1 };
    static Spell Wind = { Spell::Type::Offensive, Elements::Wind, 1 };
    static Spell Electric = { Spell::Type::Offensive, Elements::Electric, 1 };
}

#endif // EXO_SPELL_HPP
