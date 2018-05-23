
#include "GameObject.hpp"
#include "Application.hpp"

GameObject::GameObject() :
health(1), vulnerable(false), destroyed(false) {
    loadTexture("placeholder.png");
}

void GameObject::clicked(sf::Event::MouseButtonEvent event) const {
    for (auto callback : click_callbacks) {
        callback(event);
    }
}

void GameObject::die() const {
    for (auto callback : death_callbacks) {
        callback();
    }
}

GameObject& GameObject::loadTexture(std::string const& filepath, bool centered) {
    sprite.setTexture(Application::resources.getTexture(filepath), true);
    if (centered) {
        centerOrigin(true);
    }
    return *this;
}

GameObject& GameObject::centerOrigin(bool b) {
    if (b) {
        auto& rect = sprite.getTextureRect();
        sprite.setOrigin(rect.width / 2, rect.height / 2);
    }
    else {
        sprite.setOrigin(0,0);
    }
    return *this;
}

GameObject& GameObject::setPosition(float x, float y) {
    sprite.setPosition(x,y);
    return *this;
}

GameObject& GameObject::scale(float factor) {
    sprite.setScale({factor,factor});
    return *this;
}

GameObject& GameObject::onClick(std::function<void(sf::Event::MouseButtonEvent)> call) {
    click_callbacks.push_back(call);
    return *this;
}

GameObject& GameObject::onDeath(std::function<void()> call) {
    death_callbacks.push_back(call);
    return *this;
}

GameObject& GameObject::align(Alignment alignment) {
    auto position = sprite.getPosition();
    if (alignment == Alignment::Horizontal || alignment == Alignment::Both) {
        position.x = Application::context.view_size.x / 2;
    }
    if (alignment == Alignment::Vertical || alignment == Alignment::Both) {
        position.y = Application::context.view_size.y / 2;
    }
    sprite.setPosition(position);
    return *this;
}

GameObject& GameObject::setHealth(int h) {
    health = h;
    vulnerable = true;
    return *this;
}

GameObject& GameObject::setVulnerable(bool b) {
    vulnerable = b;
    return *this;
}
