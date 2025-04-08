#ifndef PLATFORMER_LIB_H
#define PLATFORMER_LIB_H

#include "glm/glm.hpp"

// Sources: 
//  Sprites
//  - https://www.spriters-resource.com/nes/mm2/
//  SFX
//  - https://www.sounds-resource.com/nes/megaman2/sound/3616/
constexpr char  PLAYER_FILEPATH[]    = "content/textures/player.png",
                ENEMY_A_FILEPATH[]   = "content/textures/enemy_a.png",
                ENEMY_B_FILEPATH[]   = "content/textures/enemy_b.png",
                ENEMY_C_FILEPATH[]   = "content/textures/enemy_c.png",
                START_FILEPATH[]     = "content/textures/start.png",
                GAME_OVER_FILEPATH[] = "content/textures/game_over.png",
                ENDING_FILEPATH[]    = "content/textures/ending.png",
                TILESET_FILEPATH[]   = "content/textures/tileset.png";

constexpr char BGM_FILEPATH[] = "content/music/wood_man.mp3";

constexpr char LAND_FILEPATH[]  = "content/sfx/land.wav",
               PRESS_FILEPATH[] = "content/sfx/press.wav",
               DEATH_FILEPATH[] = "content/sfx/death.wav";

constexpr int TILE_SIZE      = 16,
              TILESET_WIDTH  = 16,
              TILESET_HEIGHT = 12;

constexpr float TILESET_U = 1.0f / (float) TILESET_WIDTH,
                TILESET_V = 1.0f / (float) TILESET_HEIGHT;

constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

constexpr float INTERNAL_WIDTH  = 256.0f,
                INTERNAL_HEIGHT = 224.0f;

constexpr glm::vec3 PLAYER_COLLISION_OFFSET = glm::vec3(7.f, 3.f, 0.f);
constexpr float PLAYER_TEXTURE_WIDTH    = 27.f,
                PLAYER_TEXTURE_HEIGHT   = 30.f,
                PLAYER_COLLISION_WIDTH  = 13.f,
                PLAYER_COLLISION_HEIGHT = 20.f;

// Constants in pixels per second
constexpr float WALK_SPEED           = 6.f,
                WALK_SPEED_CAP       = 1.5f / FIXED_TIMESTEP,
                JUMP_SPEED           = 4.87109375f / FIXED_TIMESTEP,
                JUMP_SPEED_THRESHOLD = 2.12109375f / FIXED_TIMESTEP,
                FALL_SPEED           = 0.25f / FIXED_TIMESTEP,
                FALL_SPEED_CAP       = 7.f / FIXED_TIMESTEP;

constexpr float ENEMY_SPEED         = 0.25f / FIXED_TIMESTEP,
                ENEMY_WAIT_TIME     = 60.f / FIXED_TIMESTEP,
                ENEMY_ATTACK_TIME   = 20.f / FIXED_TIMESTEP,
                ENEMY_PROXIMITY_MIN = 7.f * TILE_SIZE;

constexpr int LIVES_AMOUNT = 3;

#endif
