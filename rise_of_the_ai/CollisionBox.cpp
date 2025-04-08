/**
* Author: Amani Hernandez (amh9766)
* Assignment: Rise of the AI
* Date due: 2025-04-07, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include "CollisionBox.h"
#include "helper.h"

CollisionBox::CollisionBox(glm::vec3 position, float width, float height)
    : m_position(position), m_prev_position(position), m_width(width), m_height(height)
{
    reset_collision();
}

glm::vec3 CollisionBox::collide_with(CollisionBox* that)
{
    float left_overlap   = calculate_left_overlap(that);
    float right_overlap  = calculate_right_overlap(that);
    float top_overlap    = calculate_top_overlap(that);
    float bottom_overlap = calculate_bottom_overlap(that);

    bool left   = left_overlap < 0.0f;
    bool right  = right_overlap > 0.0f;
    bool top    = top_overlap < 0.0f;
    bool bottom = bottom_overlap > 0.0f;

    bool prev_left   = calculate_previous_left_overlap(that) < 0.0f;
    bool prev_right  = calculate_previous_right_overlap(that) > 0.0f;
    bool prev_top    = calculate_previous_top_overlap(that) < 0.0f;
    bool prev_bottom = calculate_previous_bottom_overlap(that) > 0.0f;

    if (left && right && top && bottom)
    {
        glm::vec3 change_in_position = ZERO_VEC3;

        m_collide_left   = left != prev_left;
        m_collide_right  = right != prev_right;
        m_collide_top    = top != prev_top;
        m_collide_bottom = bottom != prev_bottom;

        that->m_collide_right = m_collide_left;
        that->m_collide_left = m_collide_right;
        that->m_collide_bottom = m_collide_top;
        that->m_collide_top = m_collide_bottom;

        if (m_collide_left)       change_in_position.x = left_overlap;
        else if (m_collide_right) change_in_position.x = right_overlap;

        if (m_collide_top)         change_in_position.y = top_overlap;
        else if (m_collide_bottom) change_in_position.y = bottom_overlap;

        m_position -= change_in_position;
        return change_in_position;
    }

    return ZERO_VEC3;
}
