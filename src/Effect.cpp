
#include "Effect.hpp"
#include "GameObject.hpp"
#include "Application.hpp"

Effect::Style Effect::LinearFade = [](float t) { return 1-t; };
Effect::Style Effect::FastPulse = [](float t) { return 6.75*(1-t)*(1-t)*t; };

Effect::Effect() :
duration(0.5), _state(State::Ready) {}

Effect::Effect(std::function<float(float)> func, std::function<void(float)> call) : Effect() {
    value_func = func;
    callback = call;
}

void Effect::update() {
    if (_state == State::Running) {
        auto elapsed = _clock.getElapsedTime().asSeconds() / duration;
        if (elapsed > 1.f) {
            _state = State::Finished;
        }
        else {
            callback(value_func(elapsed));
        }
    }
    else if (_state == State::Ready) {
        _clock.restart();
        _state = State::Running;
    }
}

const sf::Shader* Effect::getShader() {
    return _shader_ptr.get();
}

sf::Shader& Effect::setFragmentShader(const std::string& filename) {
    _shader_ptr.reset(Application::resources.allocateShader(filename, sf::Shader::Fragment));
    return *_shader_ptr;
}


Effect Effect::Flash(GameObject& target, sf::Color c, Style style) {
    float f = 0.7 / 255.f; // factor

    Effect eff;
    auto& shader = eff.setFragmentShader("tint.frag");
    eff.callback = [=, &shader](float v) {
        shader.setParameter("flashColor",c.r*f*v, c.g*f*v, c.b*f*v, c.a*f*v);
    };
    eff.value_func = style;
    return eff;
}
