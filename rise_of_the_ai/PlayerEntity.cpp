/**
* Author: Amani Hernandez (amh9766)
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "AnimatedEntity.h"
#include "PlayerEntity.h"
#include "PlatformEntity.h"
#include "platformer_lib.h"
#include "helper.h"

PlayerEntity::PlayerEntity(float width, float height, GLuint tex_id, 
    std::vector<AnimationInfo> anims, int max_frames
    )
    : AnimatedEntity(SPAWN_POINT,
        width, height, 
        tex_id,
        anims, max_frames
      ),
      m_movement(0.f), m_lives(LIVES_AMOUNT)
{
    glm::vec3 position_offset = glm::vec3(
        SPAWN_POINT.x + 7.0f,
        SPAWN_POINT.y + 3.0f,
        0.0f
    );
    m_collision = new CollisionBox(position_offset, 13.0f, 20.0f);
}

PlayerEntity::~PlayerEntity()
{
    delete m_collision;
}

bool PlayerEntity::is_out_of_bounds()
{
    return (m_position.x < -BOUND) || 
           ((m_position.x + m_width) > (INTERNAL_WIDTH + BOUND)) ||
           (m_position.y < -BOUND) ||
           ((m_position.y + m_height) > (INTERNAL_HEIGHT + BOUND));
}

void PlayerEntity::jump()
{
    if (m_collision->get_collide_bottom()) m_velocity.y = -JUMP_SPEED;
}

void PlayerEntity::fall()
{
    if (m_velocity.y < -JUMP_SPEED_THRESHOLD) m_velocity.y = -60.f;
}

void PlayerEntity::update(float delta_time, const std::vector<CollisionBox*>& map_collisions)
{ 
    // ————— PHYSICS ————— //
    if (m_movement == 0.f) m_velocity.x = 0.f;

    m_velocity.x += m_movement * WALK_SPEED;
    if (!m_collision->get_collide_bottom() || abs(m_velocity.x) > WALK_SPEED_CAP)
    {
        m_velocity.x = m_movement * WALK_SPEED_CAP;
    }

    m_velocity.y += FALL_SPEED;
    if (m_velocity.y > FALL_SPEED_CAP) m_velocity.y = FALL_SPEED_CAP;

    AnimatedEntity::update(delta_time);

    // ————— COLLISIONS ————— //
    m_collision->update_position(m_velocity * delta_time);
    m_collision->reset_collision();
    
    for (int i = 0; i < map_collisions.size(); i++)
    {
        m_position -= m_collision->collide_with(map_collisions[i]);
    }

    // Stop velocity if a collision ocurred with the map
    if (m_collision->get_collide_left() && (m_velocity.x < 0.f))   m_velocity.x = 0.f;
    if (m_collision->get_collide_right() && (m_velocity.x > 0.f))  m_velocity.x = 0.f;
    if (m_collision->get_collide_top() && (m_velocity.y < 0.f))    m_velocity.y = 0.f;
    if (m_collision->get_collide_bottom() && (m_velocity.y > 0.f)) m_velocity.y = 0.f;

    // Update animation based on movement 
    update_anim();

    // Update model matrix at the very end
    update_model_mat();
}

void PlayerEntity::update_anim()
{
    // Flip based on direction player should be facing
    if (m_movement < 0.f)      disable_x_flip();
    else if (m_movement > 0.f) enable_x_flip();

    // Set the corresponding animation
    if (m_collision->get_collide_bottom()) // Grounded
    {
        if (m_movement != 0.f) 
        {
            if (is_anim(IDLE)) set_anim(INCH);
            else if (is_anim(JUMP)) set_anim(WALK);
        }
        else if (!is_anim(BLINK)) set_anim(IDLE);
    }
    else set_anim(JUMP);
}
