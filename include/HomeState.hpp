#ifndef EXO_HOME_STATE_HPP
#define EXO_HOME_STATE_HPP

#include "State.hpp"

class HomeState : public State {

    public:
        void enter() override;
        void resume() override;

};

#endif // EXO_HOME_STATE_HPP
