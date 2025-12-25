cmake_minimum_required(VERSION 3.28)
project(Particles LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Particles main.cpp
        src/Physics/particle_simulator.hpp
        src/Physics/Particle.hpp
        src/Physics/Vector.hpp
        src/config.hpp
        src/Physics/image_analyzer.hpp
        src/state/state.hpp
        src/engine.hpp
        src/state/simulation_state.hpp
        src/state/menu_state.hpp
        src/GUI/button.hpp
        src/GUI/text_handler.hpp
        src/engine.cpp
        src/state/simulation_state.cpp
        src/state/menu_state.cpp
        src/GUI/button.cpp
        src/GUI/text_handler.cpp)
target_compile_features(Particles PRIVATE cxx_std_17)
target_link_libraries(Particles PRIVATE SFML::Graphics)