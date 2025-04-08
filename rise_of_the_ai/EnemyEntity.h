#ifndef ENEMY_ENTITY_H
#define ENEMY_ENTITY_H

#include "glm/glm.hpp"
#include "CollisionBox.h"
#include "AnimatedEntity.h"
#include "PlayerEntity.h"
#include "platformer_lib.h"
#include "helper.h"

class PlayerEntity;

enum AIType
{
    STEP_CHASE,
    CLOSE_CHASE,
    SCARED_CHASE
};

enum AIState : int
{
    WAITING   = 0,
    ATTACKING = 1
};

class EnemyEntity : public AnimatedEntity 
{
    private:
        // ————— COLLISIONS ————— //
        CollisionBox* m_collision;

        // ————— AI ————— //
        AIType m_ai_type;
        AIState m_ai_state;
        float m_accumulated_time;

    public:
        // ————— GETTERS ————— //
        CollisionBox* get_collision() const { return m_collision; }

        // ————— GENERAL ————— //
        EnemyEntity(float width, float height, GLuint tex_id, AIType ai_type);
        ~EnemyEntity();

        void update(float delta_time, PlayerEntity* player);

        // ————— GAMEPLAY ————— //
        void spawn(glm::vec3 spawn_point)
        {
            m_position     = spawn_point;
            m_velocity     = ZERO_VEC3; 
            m_acceleration = ZERO_VEC3;

            m_collision->set_position(m_position);
            m_collision->set_previous_position(m_position);
            m_accumulated_time = 0.f;
        }

        // ————— ANIMATION ————— //
        void update_anim();
};

#endif
