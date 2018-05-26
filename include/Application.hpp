#ifndef EXO_APPLICATION_HPP
#define EXO_APPLICATION_HPP

#include "Window.hpp"
#include "StateEngine.hpp"
#include "Resources.hpp"

class Application {

    public:
        Application();
        void run();

        struct Context {
            sf::Vector2u window_size;
            sf::Vector2f view_size;
        };

        struct StageData {
            int room_amount;
            int difficulty;
            bool cleared;
            std::string name;
        };

        static std::vector<StageData> stage_data;
        static Context context;
        static Resources resources;
        static StateEngine states;
        static Window window;
};

#endif // EXO_APPLICATION_HPP
