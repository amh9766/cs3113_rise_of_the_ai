#ifndef PLATFORMER_LIB_H
#define PLATFORMER_LIB_H

#include "glm/glm.hpp"

// Sources:
//      Player     - https://www.spriters-resource.com/ds_dsi/kirbysqueaksquad/sheet/2505/
//      Background - https://www.spriters-resource.com/game_boy_advance/kirbynim/sheet/2976/
//      Platform   - https://www.spriters-resource.com/game_boy_advance/kirbynim/sheet/134385/
//      Font       - https://www.spriters-resource.com/ds_dsi/kirbysqueaksquad/sheet/3337/
constexpr char  PLAYER_FILEPATH[]       = "content/player.png",
                PLATFORM_FILEPATH[]     = "content/platform.png",
                ALPHANUM_FILEPATH[]     = "content/alphanum.png",
                BACKGROUND_FILEPATH[]   = "content/background.png",
                MISSION_WON_FILEPATH[]  = "content/mission_won.png",
                MISSION_LOSS_FILEPATH[] = "content/mission_loss.png",
                TILESET_FILEPATH[] = "content/tileset.png";

constexpr char BGM_FILEPATH[] = "content/music/wood_man.mp3";

constexpr int TILE_SIZE = 16;

constexpr int TILESET_WIDTH  = 16,
              TILESET_HEIGHT = 12;

constexpr float TILESET_U = 1.0f / (float) TILESET_WIDTH,
                TILESET_V = 1.0f / (float) TILESET_HEIGHT;

constexpr float TILE_Z_MAP[] = {
    0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.5f
};

constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;



constexpr float BOUND = 100.0f;

constexpr float INTERNAL_WIDTH  = 256.0f,
                INTERNAL_HEIGHT = 224.0f;

constexpr glm::vec3 PLAYER_COLLISION_OFFSET = glm::vec3(7.f, 3.f, 0.f);
constexpr float PLAYER_TEXTURE_WIDTH = 27.f,
                PLAYER_TEXTURE_HEIGHT = 30.f,
                PLAYER_COLLISION_WIDTH = 13.f,
                PLAYER_COLLISION_HEIGHT = 20.f;

// Constants in pixels per second
constexpr float WALK_SPEED = 6.f,
                WALK_SPEED_CAP = 48.f,
                JUMP_SPEED = 3.34f / FIXED_TIMESTEP,
                JUMP_SPEED_THRESHOLD = 2.12109375f / FIXED_TIMESTEP,
                FALL_SPEED = 10.f,
                FALL_SPEED_CAP = 7.f / FIXED_TIMESTEP;

constexpr float PLATFORM_SPEED = 20.0f;

constexpr int LIVES_AMOUNT = 3;

#endif
