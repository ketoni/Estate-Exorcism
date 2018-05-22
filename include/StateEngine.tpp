
template <typename StateType>
void StateEngine::changeState(StateType&& state) {
    if (_states.size()) {
        popState();
    }
    pushState(state);
}

template <typename StateType>
void StateEngine::overlayState(StateType&& state, bool pause_previous) {
    if (pause_previous && _states.size()) {
        topState().pause();
    }
    pushState(state);
}

template <typename StateType>
void StateEngine::pushState(StateType& state) {
    auto& stored_state = accessState<StateType>();
    stored_state = state;
    _states.emplace_back(stored_state);
    topState().enter();
}

template <typename StateType>
StateType& StateEngine::accessState() const {
    static StateType state;
    return state;
}
