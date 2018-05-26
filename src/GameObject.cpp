
#include "GameObject.hpp"
#include "Application.hpp"
#include <iostream>

GameObject::GameObject() :
destroyed(false) {
    loadTexture("placeholder.png");
    text.setFont(Application::resources.getFont("arial.ttf"));
    text.setColor(sf::Color(0,0,0,255));
    text.setCharacterSize(13);
    //text.setStyle(sf::Text::Bold);
}

void GameObject::clicked(sf::Event::MouseButtonEvent event) const {
    for (auto callback : click_callbacks) {
        callback(event);
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
    text.setPosition(x,y);
    return *this;
}

GameObject& GameObject::setText(const std::string& t) {
    text.setString(t);
    std::cout << "tallasta " << text.getLocalBounds().height << std::endl;
    text.setOrigin(text.getLocalBounds().left+text.getLocalBounds().width/2, text.getLocalBounds().top+text.getLocalBounds().height/2);
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

GameObject& GameObject::onKeystroke(std::function<void(sf::Event::KeyEvent)> call) {
    keystroke_callbacks.push_back(call);
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
    text.setPosition(position);
    return *this;
}
