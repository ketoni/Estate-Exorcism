#ifndef EXO_ROOM_STATE_HPP
#define EXO_ROOM_STATE_HPP

#include "State.hpp"

class RoomState : public State {

    public:
        RoomState();
        RoomState(unsigned num_rooms);

        void enter() override;
        void update() override;

    private:
        unsigned _rooms_left;
        unsigned _num_monsters;
};

#endif // EXO_ROOM_STATE_HPP
