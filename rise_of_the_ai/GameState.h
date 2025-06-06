#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL_mixer.h>

#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "Map.h"
#include "Background.h"

struct GameState
{
    int scene_index;
    glm::mat4 view_matrix;
    PlayerEntity* player;
    EnemyEntity* enemy;
    Map* map;
    Mix_Music *bgm;
    Background* background;
};

#endif
