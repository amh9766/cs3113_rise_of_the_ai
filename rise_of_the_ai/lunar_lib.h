/**
* Author: Amani Hernandez 
* Assignment: Lunar Lander
* Date due: 2025-3-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#ifndef LUNAR_LIB_H
#define LUNAR_LIB_H

#include "glm/glm.hpp"

constexpr glm::vec3 SPAWN_POINT = glm::vec3(120.0f, 80.0f, 0.0f);

constexpr float BOUND = 100.0f;

constexpr float INTERNAL_WIDTH  = 480.0f,
                INTERNAL_HEIGHT = 320.0f;

constexpr float ACCEL_OF_GRAVITY = 2.5f,
                ACCEL_OF_PROPULSION = 15.0f,
                DRAG_COEFFICIENT = 0.25f;

constexpr float PLATFORM_SPEED = 20.0f;

constexpr int FUEL_AMOUNT = 2500,
              FUEL_USAGE = 1;

#endif

