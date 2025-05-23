/**
* Author: Amani Hernandez (amh9766)
* Assignment: Rise of the AI
* Date due: 2025-04-07, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#define GL_SILENCE_DEPRECATION
#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include <vector>

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Map.h"
#include "platformer_lib.h"
#include "helper.h"

Map::Map(int width, int height, ScrollType scroll_type, GLuint texture_id, 
    glm::vec3 player_spawn_point, glm::vec3 enemy_spawn_point,
    std::vector<int> tiles, std::vector<CollisionBox*> collisions, CollisionBox* win_collision)
    : m_width(width), m_height(height), m_scroll_type(scroll_type), m_texture_id(texture_id), 
      m_player_spawn_point(player_spawn_point), m_enemy_spawn_point(enemy_spawn_point), 
      m_collisions(collisions), m_win_collision(win_collision)
{
    m_model_mat = glm::scale(
        IDENTITY_MAT,
        glm::vec3(TILE_SIZE, TILE_SIZE, 1.0f)
    );

    int tile_count = 0;
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i] != -1) tile_count++;
    }

    m_tile_count = tile_count;
    m_vertices = new float[m_tile_count * 18];
    m_texture_coordinates = new float[m_tile_count * 12];

    int tile = 0;
    for (int i = 0; i < height; i++)
    {
        int offset = i * width; 
        for (int j = 0; j < width; j++)
        {
            int index = offset + j;

            int tile_index = tile * 12;

            int tile_id = tiles[index];

            if (tile_id != -1)
            {
                float u = (float) (tile_id % TILESET_WIDTH) * TILESET_U;
                float v = (float) (tile_id / TILESET_WIDTH) * TILESET_V;

                // Setting vertices and texture coordinates

                // Triangle 1
                // Lower left
                m_vertices[tile_index + 0] = j;
                m_vertices[tile_index + 1] = i + 1;

                m_texture_coordinates[tile_index + 0] = u;
                m_texture_coordinates[tile_index + 1] = v + TILESET_V;

                // Lower right
                m_vertices[tile_index + 2] = j + 1; 
                m_vertices[tile_index + 3] = i + 1;

                m_texture_coordinates[tile_index + 2] = u + TILESET_U;
                m_texture_coordinates[tile_index + 3] = v + TILESET_V;

                // Upper right
                m_vertices[tile_index + 4] = j + 1;
                m_vertices[tile_index + 5] = i;

                m_texture_coordinates[tile_index + 4] = u + TILESET_U;
                m_texture_coordinates[tile_index + 5] = v;

                // Triangle 2
                // Lower left
                m_vertices[tile_index + 6] = m_vertices[tile_index + 0];
                m_vertices[tile_index + 7] = m_vertices[tile_index + 1];

                m_texture_coordinates[tile_index + 6] = m_texture_coordinates[tile_index + 0];
                m_texture_coordinates[tile_index + 7] = m_texture_coordinates[tile_index + 1];

                // Upper right
                m_vertices[tile_index + 8] = m_vertices[tile_index + 4];
                m_vertices[tile_index + 9] = m_vertices[tile_index + 5];

                m_texture_coordinates[tile_index + 8] = m_texture_coordinates[tile_index + 4];
                m_texture_coordinates[tile_index + 9] = m_texture_coordinates[tile_index + 5];

                // Upper left
                m_vertices[tile_index + 10] = j;
                m_vertices[tile_index + 11] = i;

                m_texture_coordinates[tile_index + 10] = u;
                m_texture_coordinates[tile_index + 11] = v;

                tile++;
            }
        }
    }
}

Map::~Map()
{
    delete [] m_vertices;
    delete [] m_texture_coordinates;

    for (int i = 0; i < m_collisions.size(); i++) delete m_collisions[i];
}

void Map::render(ShaderProgram* program) 
{
    program->set_model_matrix(m_model_mat);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glVertexAttribPointer(program->get_position_attribute(),
        2, GL_FLOAT, false, 0, m_vertices);
    glVertexAttribPointer(program->get_tex_coordinate_attribute(),
        2, GL_FLOAT, false, 0, m_texture_coordinates);

    glDrawArrays(GL_TRIANGLES, 0, m_tile_count * 6);
}
