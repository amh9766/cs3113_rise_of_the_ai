#ifndef MAP_H
#define MAP_H

#include <vector>

#include "glm/mat4x4.hpp"
#include "CollisionBox.h"
#include "ShaderProgram.h"

enum ScrollType : unsigned int
{
    HORIZONTAL = 0b01,
    VERTICAL   = 0b10
};

class Map 
{
    private:
        // ————— GENERAL ————— //
        int m_width,
            m_height;
        int m_tile_count;
        ScrollType m_scroll_type;
        std::vector<CollisionBox*> m_collisions;

        // ————— DRAWING ————— //
        glm::mat4 m_model_mat;
        float* m_vertices,
             * m_texture_coordinates;
        GLuint m_texture_id;
        
    public:
        // ————— GENERAL ————— //
        const int get_width() const { return m_width; }
        const int get_height() const { return m_height; }
        const std::vector<CollisionBox*>& get_collisions() const { return m_collisions; }

        bool does_scroll_horizontal() const { return m_scroll_type & HORIZONTAL; }
        bool does_scroll_vertical()   const { return m_scroll_type & VERTICAL; }

        Map(int width, int height, GLuint tex_id, ScrollType scroll_type,
            std::vector<int> tile, std::vector<CollisionBox*> collisions);
        ~Map();

        void render(ShaderProgram* program);
};

#endif
