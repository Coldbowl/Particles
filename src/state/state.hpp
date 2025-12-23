#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

class Engine;

class State {
public:
     explicit State(Engine* engine) : engine(engine) {}
     virtual ~State() = default;

     virtual void update(double dt) = 0;
     virtual void render(sf::RenderWindow& window) = 0;
     virtual void enter() = 0;
     virtual void exit() = 0;
     virtual void handle_events() = 0;

protected:
     Engine* engine;
};
