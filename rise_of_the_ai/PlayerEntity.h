#ifndef PLAYER_ENTITY_H
#define PLAYER_ENTITY_H

#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "AnimatedEntity.h"
#include "PlatformEntity.h"
#include "CollisionBox.h"
#include "platformer_lib.h"

enum PlayerAnim : int
{
    NONE = -1,
    IDLE  = 0,
    BLINK = 1,
    INCH  = 2,
    WALK  = 3,
    JUMP  = 4,
    HURT  = 5
};

class PlayerEntity : public AnimatedEntity 
{
    private:
        // ————— PHYSICS ————— //
        glm::vec3 m_propulsion;

        // ————— COLLISIONS ————— //
        CollisionBox* m_collision;

        // ————— GAMEPLAY ————— //
        int m_lives;

    public:
        // ————— GETTERS ————— //
        int  const get_lives()          const { return m_lives; }

        // ————— GENERAL ————— //
        PlayerEntity(float width, float height, 
            GLuint tex_id, std::vector<AnimationInfo> anim_frames, int max_frames);
        ~PlayerEntity();

        void update(float delta_time, const std::vector<CollisionBox*>& map_collisions);

        // ————— GAMEPLAY ————— //
        void reset()
        {
            m_position = SPAWN_POINT;
            m_velocity = glm::vec3(0.0f);
            m_acceleration = glm::vec3(0.0f);

            m_lives = LIVES_AMOUNT; 
        }

        void use_live() { m_lives--; }

        // ————— PHYSICS ————— //
        void start_neutral() { m_propulsion = glm::vec3(0.0f); }

        void push_left()     { m_propulsion.x -= 1.0f; }
        void push_right()    { m_propulsion.x += 1.0f; }
        void push_up()       { m_propulsion.y -= 1.0f; }
        void push_down()     { m_propulsion.y += 1.0f; }

        bool is_out_of_bounds();

        // ————— ANIMATION ————— //
        void update_anim();
};

#endif

