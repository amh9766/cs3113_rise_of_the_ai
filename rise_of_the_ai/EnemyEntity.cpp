/**
* Author: Amani Hernandez (amh9766)
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include "glm/glm.hpp"
#include "Entity.h"
#include "CollisionBox.h"

#include "EnemyEntity.h"
#include "PlayerEntity.h"
#include "platformer_lib.h"

EnemyEntity::EnemyEntity(glm::vec3 spawn_point, float width, float height, GLuint tex_id, AIType ai_type)
    : Entity(spawn_point, width, height, tex_id), m_accumulated_time(0.f)
{
    m_ai_type = ai_type;
    m_ai_state = WAITING;
    m_collision = new CollisionBox(
        spawn_point,
        width,
        height
    );
}

void EnemyEntity::update(float delta_time, PlayerEntity* player)
{ 
    m_accumulated_time += delta_time;
    glm::vec3 player_position = player->get_position();
    float player_movement = player->get_movement();
    float to_player = glm::distance(m_position, player_position);

    switch (m_ai_state) {
        case WAITING:
            if (m_ai_type == CLOSE_CHASE && to_player < 2.f * TILE_SIZE) m_ai_state = ATTACKING;
            else if (m_ai_type == SCARED_CHASE)
            {
                if (
                    !(player_movement < 0.f && m_position.x < player_position.x)
                    && (player_movement > 0.f && m_position.x > player_position.x)
                ) m_ai_state = ATTACKING;
            }
            else m_ai_state = ATTACKING;
            break;
        case ATTACKING:
            m_velocity = glm::normalize(player->get_position() - m_position); 
            if (m_ai_type == CHASE) m_velocity *= (1 + m_accumulated_time / 5.f);
            m_velocity *= ENEMY_SPEED;
            break;
        default:
            break;
    }

    Entity::update(delta_time);

    // Update model matrix at the very end
    update_model_mat();
}
