#ifndef MAP_H
#define MAP_H

#include <vector>

#include "glm/mat4x4.hpp"
#include "CollisionBox.h"
#include "ShaderProgram.h"

enum ScrollType : int
{
    HORIZONTAL = 1,
    VERTICAL   = 2,
    BOTH       = 3
};

class Map 
{
    private:
        // ————— GENERAL ————— //
        int m_width,
            m_height;
        int m_tile_count;
        ScrollType m_scroll_type;
        glm::vec3 m_player_spawn_point;
        glm::vec3 m_enemy_spawn_point;
        std::vector<CollisionBox*> m_collisions;
        CollisionBox* m_win_collision;

        // ————— DRAWING ————— //
        glm::mat4 m_model_mat;
        float* m_vertices,
             * m_texture_coordinates;
        GLuint m_texture_id;
        
    public:
        // ————— GENERAL ————— //
        const int get_width() const { return m_width; }
        const int get_height() const { return m_height; }
        const glm::vec3 get_player_spawn_point() const { return m_player_spawn_point; }
        const glm::vec3 get_enemy_spawn_point()  const { return m_enemy_spawn_point; }
        const std::vector<CollisionBox*>& get_collisions() const { return m_collisions; }
        const CollisionBox* get_win_collision() const { return m_win_collision; }

        bool does_scroll_horizontal() const { return m_scroll_type & HORIZONTAL; }
        bool does_scroll_vertical()   const { return m_scroll_type & VERTICAL; }

        Map(int width, int height, ScrollType scroll_type, GLuint texture_id, 
            glm::vec3 player_spawn_point, glm::vec3 enemy_spawn_point,
            std::vector<int> tile, std::vector<CollisionBox*> collisions, CollisionBox* win_collision);
        ~Map();

        void render(ShaderProgram* program);
};

#endif
