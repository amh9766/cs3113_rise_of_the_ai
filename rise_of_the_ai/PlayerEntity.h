#ifndef PLAYER_ENTITY_H
#define PLAYER_ENTITY_H

#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "AnimatedEntity.h"
#include "PlatformEntity.h"
#include "CollisionBox.h"
#include "platformer_lib.h"
#include "helper.h"

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
        float m_movement;

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
        void jump();
        void fall();

        void reset()
        {
            m_position     = SPAWN_POINT;
            m_velocity     = ZERO_VEC3; 
            m_acceleration = ZERO_VEC3;

            m_lives = LIVES_AMOUNT; 
        }

        void use_live() { m_lives--; }

        // ————— PHYSICS ————— //
        void start_neutral() { m_movement = 0.f; }

        void move_left()     { m_movement -= 1.0f; }
        void move_right()    { m_movement += 1.0f; }

        bool is_out_of_bounds();

        // ————— ANIMATION ————— //
        void update_anim();
};

#endif

