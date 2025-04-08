#ifndef LEVEL_A_H
#define LEVEL_A_H

#include <SDL.h>
#include <SDL_mixer.h>

#include "LevelScene.h"
#include "CollisionBox.h"
#include "Map.h"
#include "platformer_lib.h"
#include "helper.h"

class LevelA : public LevelScene
{
    public:
        LevelA(int next_scene_index, PlayerEntity* player, GLuint texture_id)
            : LevelScene(next_scene_index, player)
        {
            m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
            
            // ————— MAP ————— //
            CollisionBox* win_collision = new CollisionBox(
                glm::vec3(23.f * TILE_SIZE, 4.f * TILE_SIZE, 0.f),
                2.f * TILE_SIZE,
                1.f * TILE_SIZE
            );
            m_game_state.map = new Map(
                35,
                14,
                HORIZONTAL,
                texture_id,
                glm::vec3(8.f * TILE_SIZE, 9.f * TILE_SIZE, 0.f),
                {
                    -1,-1,81,82,-1,-1,-1,4,5,5,5,5,6,-1,-1,-1,4,5,6,-1,-1,-1,-1,-1,-1,-1,-1,4,5,5,5,6,-1,-1,-1,
                    -1,96,97,98,-1,-1,-1,-1,-1,-1,-1,-1,4,5,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                    -1,112,113,114,115,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,5,5,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,5,5,6,
                    18,19,19,19,19,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                    18,37,52,53,37,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,154,155,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                    18,37,68,69,37,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,48,49,49,50,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                    18,37,37,37,37,20,65,65,65,65,-1,-1,-1,-1,-1,-1,-1,48,49,50,-1,-1,51,51,51,51,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                    18,37,37,37,37,20,64,64,64,64,-1,-1,-1,-1,-1,-1,-1,51,51,51,-1,-1,67,66,67,66,-1,-1,-1,48,49,50,-1,-1,-1,
                    18,37,37,37,37,20,64,64,64,64,-1,-1,-1,-1,-1,-1,-1,67,66,67,-1,-1,67,67,67,67,-1,-1,-1,67,67,67,-1,-1,-1,
                    18,37,37,37,37,20,64,64,64,64,-1,-1,-1,-1,-1,-1,-1,67,67,66,-1,-1,66,67,16,17,17,-1,-1,66,67,67,-1,-1,-1,
                    18,37,37,37,37,20,80,64,64,64,-1,-1,-1,-1,-1,-1,-1,66,67,67,-1,-1,67,67,32,33,32,-1,-1,67,67,66,-1,-1,-1,
                    32,33,32,33,32,33,16,17,16,17,16,17,16,17,16,17,16,17,16,17,16,17,16,17,32,32,32,-1,-1,67,67,67,-1,-1,-1,
                    32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,-1,-1,67,66,67,-1,-1,-1,
                    32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,-1,-1,67,67,67,-1,-1,-1
                },
                {
                    new CollisionBox(
                        ZERO_VEC3,
                        6.f  * TILE_SIZE,
                        14.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(24.f * TILE_SIZE, 9.f * TILE_SIZE, 0.f),
                        3.f * TILE_SIZE,
                        3.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(29.f * TILE_SIZE, 7.f * TILE_SIZE, 0.f),
                        3.f * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    win_collision,
                    new CollisionBox(
                        glm::vec3(22.f * TILE_SIZE, 5.f * TILE_SIZE, 0.f),
                        4.f * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(17.f * TILE_SIZE, 6.f * TILE_SIZE, 0.f),
                        3.f * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(0.f, 11.f * TILE_SIZE, 0.f),
                        27.f * TILE_SIZE,
                        3.f * TILE_SIZE
                    )
                },
                win_collision
            );
        }
        
        void initialise() override
        {
            // ————— GAME STATE ————— //
            m_game_state.scene_index = 3;

            Mix_PlayMusic(m_game_state.bgm, -1);
            Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

            // ————— RENDERING ————— //
            glClearColor(
                    24.0f / 255.0f, 
                    60.0f / 255.0f,
                    92.0f / 255.0f, 
                    1.0f
                    );

            m_game_state.player->reset_lives();

            LevelScene::initialise();
        }
};

#endif

