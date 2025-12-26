cmake_minimum_required(VERSION 3.28)
project(Particles LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Particles main.cpp
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
        src/GUI/text_handler.cpp
        src/Physics/Particles.hpp
)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

find_package(OpenMP REQUIRED)

# Force OpenMP on MinGW (important)
target_compile_options(Particles PRIVATE -fopenmp)
target_link_options(Particles PRIVATE -fopenmp)

target_link_libraries(Particles
        PRIVATE
        SFML::Graphics
        OpenMP::OpenMP_CXX
)