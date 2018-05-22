
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

void StateEngine::drawAll(Window& renderer) {
    for (auto& state_ref : _states) {
        for (auto& obj : state_ref.get().getGameObjects()) {
            renderer.draw(obj);
        }
    }
}

std::vector<GameObject> const& StateEngine::getUIObjects() const {
    if (_states.empty()) {
        throw std::runtime_error("No States to get objects from");
    }
    return topState().getGameObjects();
}

void StateEngine::popState() {
    topState().exit();
    _states.pop_back();
}

State& StateEngine::topState() const {
    return _states.back().get();
}
