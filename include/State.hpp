#ifndef EXO_STATE_HPP
#define EXO_STATE_HPP

#include <vector>
#include "GameObject.hpp"
#include "Window.hpp"

class State {

    public:
        State();
        virtual ~State();

        virtual void enter() {}
        virtual void resume() {}
        virtual void pause() {}
        virtual void exit() {}

        virtual void update();

        void terminate();
        bool isTerminating() const;

        std::vector<GameObject>& getGameObjects();

    protected:
        GameObject& newGameObj();

    private:
        bool _terminating;
        std::vector<GameObject> _objects;

};

#endif // EXO_STATE_HPP
