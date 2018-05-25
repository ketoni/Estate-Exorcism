#ifndef EXO_EFFECT_HPP
#define EXO_EFFECT_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include <memory>

class GameObject; // Forward declaration

class Effect {

    public:

        Effect(std::function<float(float)> value_func, std::function<void(float)> callback);

        // Public types
        typedef std::function<float(float)> Style;
        enum State {
            Ready,
            Running,
            Finished,
        };

        // Methods
        void update();

        const sf::Shader* getShader();
        sf::Shader& setFragmentShader(const std::string& filename);

        // Static methods
        static Effect Flash(sf::Color color, Style style);

        // Static members
        static Style LinearFade;
        static Style FastPulse;

        // Members
        Style value_func;
        std::function<void(float)> callback;
        float duration;

    private:
        Effect();

        std::shared_ptr<sf::Shader> _shader_ptr;
        sf::Clock _clock;
        State _state;
};

#endif // EXO_EFFECT_HPP
