#ifndef EXO_ROOM_STATE_HPP
#define EXO_ROOM_STATE_HPP

#include "State.hpp"
#include "Monster.hpp"
#include "Application.hpp"

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

        int _stage_index;
        int _rooms_left;
        std::vector<Monster> _monsters;
};

#endif // EXO_ROOM_STATE_HPP
