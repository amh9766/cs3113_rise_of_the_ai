#ifndef ENEMY_ENTITY_H
#define ENEMY_ENTITY_H

#include "glm/glm.hpp"
#include "CollisionBox.h"
#include "Entity.h"
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

enum AIState
{
    WAITING,
    ATTACKING
};

class EnemyEntity : public Entity
{
    private:
        AIType m_ai_type;
        AIState m_ai_state;
        CollisionBox* m_collision;
        float m_accumulated_time;

    public:
        CollisionBox* get_collision() const { return m_collision; }

        EnemyEntity(float width, float height, GLuint tex_id, AIType ai_type);
        ~EnemyEntity();

        void spawn(glm::vec3 spawn_point)
        {
            m_position     = spawn_point;
            m_velocity     = ZERO_VEC3; 
            m_acceleration = ZERO_VEC3;

            m_collision->set_position(m_position);
            m_collision->set_previous_position(m_position);
            m_accumulated_time = 0.f;
        }

        void update(float delta_time, PlayerEntity* player);
};

#endif
