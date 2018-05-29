
#include "Effect.hpp"
#include "GameObject.hpp"
#include "Application.hpp"

Effect::Style Effect::LinearIn = [](float t) { return t; };
Effect::Style Effect::LinearOut = [](float t) { return 1-t; };
Effect::Style Effect::FastIn = [](float t) { return 1-(1-t)*(1-t)*(1-t); };
Effect::Style Effect::FastOut = [](float t) { return (1-t)*(1-t)*(1-t); };
Effect::Style Effect::SlowIn = [](float t) { return t*t*t; };
Effect::Style Effect::SlowOut = [](float t) { return 1-t*t*t; };
Effect::Style Effect::FastPulse = [](float t) { return 6.75*(1-t)*(1-t)*t; };
Effect::Style Effect::SlowPulse = [](float t) { return 6.75*(1-t)*t*t; };

Effect::Effect(float d, bool l) :
duration(d), loop(l), _state(State::Ready) {}

void Effect::update(GameObject& target) {
    if (_state == State::Running) {
        auto elapsed = _clock.getElapsedTime().asSeconds() / duration;
        if (elapsed > 1.f) {
            callback(target, value_func(1));
            if (loop) {
                _clock.restart();
            }
            else {
                _state = State::Finished;
            }
        }
        else {
            callback(target, value_func(elapsed));
        }
    }
    else if (_state == State::Ready) {
        _clock.restart();
        callback(target, value_func(0));
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

Effect Effect::Tint(sf::Color c, Style style) {
    float f = 1.0 / 255.f; // factor

    Effect eff;
    auto& shader = eff.setFragmentShader("tint.frag");
    eff.callback = [=, &shader](auto& obj, float v) {
        shader.setParameter("flashColor",c.r*f*v, c.g*f*v, c.b*f*v, c.a*f*v);
    };
    eff.value_func = style;
    return eff;
}

Effect Effect::Fade(Style style) {
    Effect eff;
    eff.callback = [](auto& obj, float v) {
        auto c = obj.sprite.getColor();
        c.a = v * 255;
        obj.sprite.setColor(c);
    };
    eff.value_func = style;
    return eff;
}

Effect Effect::Move(GameObject& obj, const sf::Vector2f& amount, Style style) {
    Effect eff(0.5);
    auto orig_pos = obj.sprite.getPosition();
    eff.callback = [=](auto& obj, float v) {
        obj.sprite.setPosition(orig_pos + v * amount);
    };
    eff.value_func = style;
    return eff;
}

