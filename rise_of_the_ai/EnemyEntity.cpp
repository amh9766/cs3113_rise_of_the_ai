/**
* Author: Amani Hernandez (amh9766)
* Assignment: Rise of the AI
* Date due: 2025-04-07, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include "glm/glm.hpp"
#include "CollisionBox.h"
#include "AnimatedEntity.h"
#include "EnemyEntity.h"
#include "PlayerEntity.h"
#include "platformer_lib.h"

EnemyEntity::EnemyEntity(float width, float height, GLuint tex_id, AIType ai_type)
    : AnimatedEntity(ZERO_VEC3, width, height, tex_id,
        {
            { 1, 0, -1, FIXED_TIMESTEP },
            { 1, 0, -1, FIXED_TIMESTEP }
        }, 1
    ), 
    m_accumulated_time(0.f)
{
    m_ai_type = ai_type;
    m_ai_state = WAITING;
    m_collision = new CollisionBox(
        ZERO_VEC3,
        width,
        height
    );
}

EnemyEntity::~EnemyEntity()
{
    delete m_collision;
}

void EnemyEntity::update(float delta_time, PlayerEntity* player)
{ 
    glm::vec3 player_position = player->get_position() + PLAYER_COLLISION_OFFSET;
    glm::vec3 from_enemy_to_player = player_position - m_position;

    m_accumulated_time += delta_time;
    bool facing_right = player->is_horizontally_flipped();
    float distance_between = glm::length(from_enemy_to_player);
    glm::vec3 normalized_direction = from_enemy_to_player / distance_between;

    
    bool player_facing_enemy = (facing_right && m_position.x >= player_position.x)
                               || (!facing_right && m_position.x <= player_position.x);

    switch (m_ai_state) 
    {
        case WAITING:
            set_anim(WAITING);
            m_velocity = ZERO_VEC3;
            switch (m_ai_type)
            {
                case STEP_CHASE:
                    if (m_accumulated_time > ENEMY_WAIT_TIME) m_ai_state = ATTACKING;
                    break;
                case CLOSE_CHASE:
                    if (distance_between <= ENEMY_PROXIMITY_MIN) m_ai_state = ATTACKING;
                    break;
                case SCARED_CHASE:
                    if (!player_facing_enemy) m_ai_state = ATTACKING;
                    break;
            }
            break;
        case ATTACKING:
            set_anim(ATTACKING);
            switch (m_ai_type)
            {
                case STEP_CHASE:
                    if (m_velocity == ZERO_VEC3) 
                        m_velocity = normalized_direction * (1.f + m_accumulated_time) * ENEMY_SPEED * 7.f;
                    else if (m_accumulated_time >= ENEMY_WAIT_TIME + ENEMY_ATTACK_TIME)
                    {
                        m_accumulated_time = 0.f;
                        m_ai_state = WAITING;
                    }
                    break;
                case SCARED_CHASE:
                    m_velocity = normalized_direction * (1.f + m_accumulated_time / 4.f) * ENEMY_SPEED; 
                    if (player_facing_enemy) m_ai_state = WAITING; 
                    break;
                case CLOSE_CHASE:
                    m_velocity = normalized_direction * (1.f + m_accumulated_time / 2.f) * ENEMY_SPEED;
                    if (distance_between > ENEMY_PROXIMITY_MIN) m_ai_state = WAITING;
                    break;
            }
            break;
        default:
            break;
    }

    AnimatedEntity::update(delta_time);

    m_collision->reset_collision();
    m_collision->update_position(m_velocity * delta_time);

    // Update animation based on movement 
    update_anim();

    // Update model matrix at the very end
    update_model_mat();
}

void EnemyEntity::update_anim()
{
    if (m_velocity.x < 0.f) disable_x_flip();
    else if (m_velocity.x > 0.f) enable_x_flip();
}
