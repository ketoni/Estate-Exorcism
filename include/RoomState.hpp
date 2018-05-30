#ifndef EXO_ROOM_STATE_HPP
#define EXO_ROOM_STATE_HPP

#include "State.hpp"
#include "Monster.hpp"
#include "Application.hpp"

class Rune : public GameObject {

    public:
        Rune(Element e) : element(e) {}
        Element element;
};


class RoomState : public State {

    public:
        RoomState();
        RoomState(int index, int rooms_left);

        void enter() override;
        void update() override;
        void exit() override;

    private:
        Monster& newMonster(Monster::Type type);
        void monsterCycle();

        void spellCycle();
        Element determineElement(DrawAnalyzer::Shape shape);
        void stackElement(Element element);
        std::vector<Element> _elements_available;
        std::vector<Rune> _rune_stack;

        int _stage_index;
        int _rooms_left;
        std::vector<Monster> _monsters;
};

#endif // EXO_ROOM_STATE_HPP
