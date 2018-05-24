#ifndef EXO_ROOM_STATE_HPP
#define EXO_ROOM_STATE_HPP

#include "State.hpp"
#include "Monster.hpp"

class RoomState : public State {

    public:
        RoomState();
        RoomState(unsigned num_rooms);

        void enter() override;
        void update() override;

    private:
        Monster& newMonster(Monster::Type type);

        unsigned _rooms_left;
        std::vector<Monster> _monsters;
};

#endif // EXO_ROOM_STATE_HPP
