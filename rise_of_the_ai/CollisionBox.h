#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "glm/vec3.hpp"

class CollisionBox
{
    private:
        glm::vec3 m_prev_position,
                  m_position;
        float m_height, m_width;
        bool m_collide_bottom,
             m_collide_top,
             m_collide_left,
             m_collide_right;


    public: 
        CollisionBox(glm::vec3 position, float width, float height);

        // ————— GETTERS ————— //
        bool get_collide_bottom() const { return m_collide_bottom; }
        bool get_collide_top()    const { return m_collide_top; }
        bool get_collide_left()   const { return m_collide_left; }
        bool get_collide_right()  const { return m_collide_right; }

        // ————— SETTERS ————— //
        void set_position(glm::vec3 new_position)          { m_position = new_position; }
        void set_previous_position(glm::vec3 new_position) { m_prev_position = new_position; }

        // ————— GENERAL ————— //
        bool did_collide() const { return m_collide_bottom || m_collide_top || m_collide_left || m_collide_right; }

        float calculate_left_overlap(CollisionBox* that)   { return m_position.x - (that->m_position.x + that->m_width); }
        float calculate_right_overlap(CollisionBox* that)  { return m_position.x + m_width - that->m_position.x; }
        float calculate_top_overlap(CollisionBox* that)    { return m_position.y - (that->m_position.y + that->m_height); }
        float calculate_bottom_overlap(CollisionBox* that) { return m_position.y + m_height - that->m_position.y; }

        float calculate_previous_left_overlap(CollisionBox* that)   { return m_prev_position.x - (that->m_position.x + that->m_width); }
        float calculate_previous_right_overlap(CollisionBox* that)  { return m_prev_position.x + m_width - that->m_position.x; }
        float calculate_previous_top_overlap(CollisionBox* that)    { return m_prev_position.y - (that->m_position.y + that->m_height); }
        float calculate_previous_bottom_overlap(CollisionBox* that) { return m_prev_position.y + m_height - that->m_position.y; }

        void update_position(glm::vec3 change_in_position) { m_prev_position = m_position; m_position += change_in_position; }

        void reset_collision()
        {
            m_collide_bottom = false; 
            m_collide_top    = false;
            m_collide_left   = false;
            m_collide_right  = false;
        }

        glm::vec3 collide_with(CollisionBox* that);
};

#endif
