
#include "State.hpp"

State::State() :
_terminating(false), _objects() {
    _objects.reserve(10); // TODO fix properly
}

State::~State() {}

void State::update() {
    auto it = _objects.begin();
    while (it != _objects.end()) {
        if (it->destroyed) {
            _objects.erase(it);
        }
        else {
            ++it;
        }
    }
}

void State::terminate() {
    _terminating = true;
}

bool State::isTerminating() const {
    return _terminating;
}

std::vector<GameObject>& State::getGameObjects() {
    return _objects;
}

GameObject& State::newGameObject() {
    _objects.emplace_back();
    return _objects.back();
}

