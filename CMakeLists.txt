project(R-TYPE)               # SCreate project "simple_example"
cmake_minimum_required(VERSION 3.11)   # CMake version check

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard
set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/GameEngine)  # Set GameEngine Directory
set(ENGINE_SRC ${ENGINE_DIR}/Entity/Entity.cpp ${ENGINE_DIR}/Manager/Manager.cpp
        ${ENGINE_DIR}/Components/DamageComponent/DamageComponent.cpp
        ${ENGINE_DIR}/Components/DeliverComponent/DeliverComponent.cpp
        ${ENGINE_DIR}/Components/GraphicsComponent/GraphicsComponent.cpp
        ${ENGINE_DIR}/Components/HealthComponent/HealthComponent.cpp
        ${ENGINE_DIR}/Components/NicknameComponent/NicknameComponent.cpp
        ${ENGINE_DIR}/Components/PositionComponent/PositionComponent.cpp
        ${ENGINE_DIR}/Components/PowerComponent/PowerComponent.cpp
        ${ENGINE_DIR}/Components/PowerupComponent/PowerupComponent.cpp
        ${ENGINE_DIR}/Components/ScoreComponent/ScoreComponent.cpp
        ${ENGINE_DIR}/Components/SpeedComponent/SpeedComponent.cpp
        ${ENGINE_DIR}/System/MovementSystem/MovementSystem.cpp) # Add the GameEngine SRC

subdirs(Client Server)
