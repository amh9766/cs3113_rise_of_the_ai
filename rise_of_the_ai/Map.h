#ifndef MAP_H
#define MAP_H

#include <vector>

#include "glm/glm.hpp"
#include "CollisionBox.h"
#include "ShaderProgram.h"

class Map 
{
    private:
        // ————— GENERAL ————— //
        int m_width,
            m_height;
        int m_tile_count;
        std::vector<CollisionBox*> m_collisions;

        // ————— DRAWING ————— //
        glm::mat4 m_model_mat;
        float* m_vertices,
             * m_texture_coordinates;
        GLuint m_texture_id;
        
    public:
        // ————— GENERAL ————— //
        const std::vector<CollisionBox*>& get_collisions() const { return m_collisions; }

        Map(int width, int height, GLuint tex_id, std::vector<int> tile, std::vector<CollisionBox*> collisions);
        ~Map();

        void render(ShaderProgram* program);
};

#endif
