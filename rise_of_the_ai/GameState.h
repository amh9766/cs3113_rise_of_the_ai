#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL_mixer.h>

#include "PlayerEntity.h"
#include "Map.h"
#include "Background.h"

struct GameState
{
    PlayerEntity* player;
    Map* map;

    Mix_Music *bgm;

    Background* mission_won;
    Background* mission_loss;
};

#endif
