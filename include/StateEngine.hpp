#ifndef EXO_STATE_ENGINE_HPP
#define EXO_STATE_ENGINE_HPP

#include <vector>
#include <functional>
#include "State.hpp"
#include "Window.hpp"

class StateEngine {

    public:
        StateEngine();

        template <typename StateType>
        void changeState(StateType&& state);
        template <typename StateType>
        void overlayState(StateType&& state, bool pause_previous = false);
        template <typename StateType>
        StateType& accessState() const;

        bool update();
        void flush();

        void handDrawables(Window& renderer);
        void handObjects(Window& renderer);

    private:
        template <typename StateType>
        void pushState(StateType& state);
        void popState();
        State& topState() const;

        std::vector<std::reference_wrapper<State>> _states;

};

#include "StateEngine.tpp"

#endif // EXO_STATE_ENGINE_HPP
