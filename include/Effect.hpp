#ifndef EXO_EFFECT_HPP
#define EXO_EFFECT_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include <memory>

class GameObject; // Forward declaration

class Effect {

    public:

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
        static Effect Flash(sf::Color color, Style style);
        static Effect Nudge(GameObject& obj, const sf::Vector2f& amount, Style style);

        // Static members
        static Style LinearFade;
        static Style FastPulse;

        // Members
        Style value_func;
        std::function<void(GameObject&, float)> callback;
        float duration;
        bool loop;

    private:
        Effect();

        std::shared_ptr<sf::Shader> _shader_ptr;
        sf::Clock _clock;
        State _state;
};

#endif // EXO_EFFECT_HPP
