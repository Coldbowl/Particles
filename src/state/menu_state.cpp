#include <array>
#include <memory>
#include <iostream>
#include <filesystem>

#include "state.hpp"
#include "../GUI/button.hpp"
#include "menu_state.hpp"
#include "../config.hpp"
#include "../engine.hpp"
#include "simulation_state.hpp"
#include "../External/tinyfiledialogs.h"

MenuState::MenuState(Engine* engine, sf::RenderWindow& window)
    : State(engine)
    , window{window}
    , title_text{
        "Particle Simulator",
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
        window,
        sf::Color::Cyan,
        100
    }
{
    buttons[0] = std::make_unique<Button>(
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT * 3.0 / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
        "Simulate",
        window,
        [this]() {
            this->engine->change_state(new SimulationState(this->engine, this->window));
        }
    );
    buttons[1] = std::make_unique<Button>(
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT * 4.0 / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
    "Upload Image",
        window, []() {
            const char* filters[] = { "*.png", "*.jpg", "*.jpeg", "*.bmp" };

            const char* selectedPath = tinyfd_openFileDialog(
                "Select an image",
                "",
                4,
                filters,
                "Image files",
                0
            );

            if (!selectedPath) {
                std::cout << "User cancelled\n";
                return;
            }

            std::cout << "Selected: " << selectedPath << "\n";

            namespace fs = std::filesystem;

            fs::path dest = "src/Image/particles_image.png";

            // Ensure directory exists
            fs::create_directories(dest.parent_path());

            // Windows-safe overwrite
            if (fs::exists(dest)) {
                fs::remove(dest);
            }

            fs::copy_file(selectedPath, dest);
        }
    );
    buttons[2] = std::make_unique<Button>(
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT * 5.0 / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
        "Quit",
        window,
        [this]() {
            this->engine->quit();
        }
    );
}

void MenuState::update(float dt) {
    position = sf::Mouse::getPosition(window);
}

void MenuState::render(sf::RenderWindow& window) {
    title_text.render_text();

    is_hovering = false;
    for (const auto& btn : buttons) {
        if (!btn) continue;

        Button& b = *btn;

        if (b.is_hovering(position)) {
            hovered_button = &b;
            is_hovering = true;
        }
        b.draw(); // <---- The reason all of this is even in render, is because of this cheeky call
    }
    if (!is_hovering) {
        hovered_button = nullptr;
    }
}

void MenuState::enter()  {
    // TODO: code for when this state becomes active
}

void MenuState::exit()  {
    // TODO: code for when this state exits
}

void MenuState::handle_events()  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (!pressed) {
            if (hovered_button != nullptr) hovered_button->clicked();
            pressed = true;
        }
    } else {
        pressed = false;
    }
}