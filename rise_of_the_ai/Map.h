#ifndef MAP_H
#define MAP_H

#include <vector>

#include "glm/glm.hpp"
#include "ShaderProgram.h"

enum TileType
{
    BACKGROUND,
    FOREGROUND
};

struct Tile
{
    int id;
    float z;
};

class Map 
{
    private:
        // ————— GENERAL ————— //
        int m_width,
            m_height;
        int m_tile_count;

        // ————— DRAWING ————— //
        glm::mat4 m_model_mat;
        float* m_vertices,
             * m_texture_coordinates;
        GLuint m_texture_id;
        
    public:
        // ————— GENERAL ————— //
        Map(int width, int height, GLuint tex_id, std::vector<Tile> tiles);
        ~Map();

        void render(ShaderProgram* program);
};

#endif
