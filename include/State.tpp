
State::State() :
_terminating(false), _paused(true), _objects() {}

void State::enter() {
    _paused = false;
}

void State::resume() {
    if (!_paused) {
        return;
    }
    _paused = false;
}

void State::pause() {
    if (_paused) {
        return;
    }
    _paused = true;
}

void State::exit() {
    _paused = true;
}

void State::update() {
    if (_paused) {
        return;
    }
}

bool State::isTerminating() {
    return _terminating;
}

bool State::isPaused() {
    return _paused;
}

std::vector<GameObject> const& State::getGameObjects() {
    return _objects;
}

void State::terminate() {
    _terminating = true;
}

GameObject& State::addGameObject(GameObject&& obj) {
    _objects.push_back(obj);
    return _objects.back();
}
