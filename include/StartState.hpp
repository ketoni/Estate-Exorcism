#ifndef EXO_START_STATE_HPP
#define EXO_START_STATE_HPP

#include "State.hpp"

class StartState : public State {

    public:
        void enter() override;
        bool quit = false;
};

#endif // EXO_START_STATE_HPP
