#ifndef PLAYER_ENTITY_H
#define PLAYER_ENTITY_H

#include <SDL_mixer.h>

#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "AnimatedEntity.h"
#include "EnemyEntity.h"
#include "Map.h"
#include "platformer_lib.h"
#include "helper.h"

class EnemyEntity;

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

        // ————— SOUND ————— //
        Mix_Chunk* m_land_sfx;
        Mix_Chunk* m_death_sfx;

        // ————— GAMEPLAY ————— //
        int m_lives;

    public:
        // ————— GETTERS ————— //
        CollisionBox* const get_collision() const { return m_collision; }
        float const get_movement() const { return m_movement; }
        int  const get_lives() const { return m_lives; }

        // ————— GENERAL ————— //
        PlayerEntity(GLuint tex_id, std::vector<AnimationInfo> anim_frames, int max_frames);
        ~PlayerEntity();

        void update(float delta_time, Map* map, EnemyEntity* enemy);

        // ————— GAMEPLAY ————— //
        void jump();
        void fall();

        void spawn(glm::vec3 spawn_point)
        {
            m_position     = spawn_point;
            m_velocity     = ZERO_VEC3; 
            m_acceleration = ZERO_VEC3;

            m_collision->set_position(m_position + PLAYER_COLLISION_OFFSET);
            m_collision->set_previous_position(m_position + PLAYER_COLLISION_OFFSET);
        }

        void respawn(glm::vec3 spawn_point)
        {
            spawn(spawn_point);
            m_lives--;
        }

        void reset_lives() { m_lives = LIVES_AMOUNT; }

        // ————— PHYSICS ————— //
        void start_neutral() { m_movement = 0.f; }

        void move_left()     { m_movement -= 1.0f; }
        void move_right()    { m_movement += 1.0f; }

        // ————— ANIMATION ————— //
        void update_anim();
};

#endif

