
#include "State.hpp"

State::State() :
_terminating(false), _objects() {}

State::~State() {}

void State::terminate() {
    _terminating = true;
}

bool State::isTerminating() const {
    return _terminating;
}

std::vector<GameObject>& State::getGameObjects() {
    return _objects;
}

GameObject& State::newGameObj() {
    _objects.emplace_back();
    return _objects.back();
}
