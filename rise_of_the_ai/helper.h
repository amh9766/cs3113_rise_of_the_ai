#ifndef HELPER_H
#define HELPER_H

#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES 1
#ifdef _WINDOWS
    #include <GL/glew.h>
#endif

#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

#define LOG(argument) std::cout << argument << '\n'

constexpr glm::mat4 IDENTITY_MAT = glm::mat4(1.0f);

constexpr float STANDARD_COORDINATES[] =
{
    // Triangle 1
    0.0f, 1.0f,  // Lower left
    1.0f, 1.0f,  // Lower right
    1.0f, 0.0f,  // Upper right
    // Triangle 2
    0.0f, 1.0f,  // Lower left
    1.0f, 0.0f,  // Upper right
    0.0f, 0.0f   // Upper left
};

constexpr glm::vec3 ZERO_VEC3 = glm::vec3(0.0f);

void print_matrix(glm::mat4 &matrix, int size);
GLuint load_texture(const char* filepath);

#endif
