#ifndef ENEMY_ENTITY_H
#define ENEMY_ENTITY_H

#include "glm/glm.hpp"
#include "Entity.h"
#include "PlayerEntity.h"
#include "CollisionBox.h"
#include "platformer_lib.h"
#include "helper.h"

enum AIType
{
    CHASE,
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
        glm::vec3 m_spawn_point;
        float m_accumulated_time;

    public:
        EnemyEntity(glm::vec3 spawn_point, float width, float height, GLuint tex_id, AIType ai_type);
        ~EnemyEntity();
        const CollisionBox* get_collision() const { return m_collision; }

        void spawn(glm::vec3 spawn_point)
        {
            m_position     = m_spawn_point;
            m_velocity     = ZERO_VEC3; 
            m_acceleration = ZERO_VEC3;

            m_collision->set_position(m_position);
            m_collision->set_previous_position(m_position);
            m_accumulated_time = 0.f;
        }

        void update(float delta_time, PlayerEntity* map);
};

#endif
