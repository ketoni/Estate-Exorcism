#ifndef EXO_EFFECT_HPP
#define EXO_EFFECT_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include <memory>

class GameObject; // Forward declaration

class Effect {

    public:
        Effect(float duration = 0.3, bool loop = false);

        // Public types
        typedef std::function<float(float)> Style;
        enum State {
            Ready,
            Running,
            Finished,
        };

        // Methods
        void update(GameObject& target);

        const sf::Shader* getShader();
        sf::Shader& setFragmentShader(const std::string& filename);

        // Static methods
        static Effect Tint(sf::Color color, Style style);
        static Effect Fade(Style style);
        static Effect Move(GameObject& obj, const sf::Vector2f& amount, Style style);

        // Static members
        static Style LinearIn;
        static Style LinearOut;
        static Style FastIn;
        static Style FastOut;
        static Style SlowIn;
        static Style SlowOut;
        static Style FastPulse;
        static Style SlowPulse;

        // Members
        Style value_func;
        std::function<void(GameObject&, float)> callback;
        float duration;
        bool loop;

    private:
        std::shared_ptr<sf::Shader> _shader_ptr;
        sf::Clock _clock;
        State _state;
};

#endif // EXO_EFFECT_HPP
