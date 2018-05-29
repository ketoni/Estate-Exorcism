
#include "StateEngine.hpp"

StateEngine::StateEngine() :
 _states() {}

bool StateEngine::update() {
    if (_states.empty()) {
        return false;
    }
    if (topState().isTerminating()) {
        popState();
        if (_states.size()) {
            topState().resume();
        }
        else {
            return false;
        }
    }
    for (auto& state_ref : _states) {
        state_ref.get().update();
    }
    return true;
}

void StateEngine::flush() {
    while (_states.size()) {
        popState();
    }
}

void StateEngine::handDrawables(Window& renderer) {
    for (auto& state_ref : _states) {
        for (auto& obj : state_ref.get().getGameObjects()) {
            renderer.draw(obj);
        }
    }
}

void StateEngine::handObjects(Window& window) {
    for (auto& obj : topState().getGameObjects()) {
        window.handleGameEvents(obj);
    }
}

void StateEngine::popState() {
    topState().exit();
    _states.pop_back();
}

State& StateEngine::topState() const {
    return _states.back().get();
}
