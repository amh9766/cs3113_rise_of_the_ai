#ifndef LEVEL_B_H
#define LEVEL_B_H

#include <SDL.h>
#include <SDL_mixer.h>

#include "LevelScene.h"
#include "CollisionBox.h"
#include "Map.h"
#include "platformer_lib.h"
#include "helper.h"

class LevelB : public LevelScene
{
    public:
        LevelB(int next_scene_index, PlayerEntity* player, GLuint texture_id)
            : LevelScene(next_scene_index, player)
        {
            m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);

            // ————— MAP ————— //
            CollisionBox* win_collision = new CollisionBox(
                glm::vec3(3.f * TILE_SIZE, 5.f * TILE_SIZE, 0.f),
                2.f * TILE_SIZE,
                1.f * TILE_SIZE
            );
            m_game_state.map = new Map(
                16,
                19,
                VERTICAL,
                texture_id,
                glm::vec3(2.f * TILE_SIZE, 13.f * TILE_SIZE, 0.f),
                glm::vec3(13.f * TILE_SIZE, 10.f * TILE_SIZE, 0.f),
                {
                    18,37,19,34,35,36,19,37,37,19,34,35,36,19,37,20,
                    18,44,44,44,44,44,44,44,44,44,44,44,44,44,44,20,
                    18,45,45,45,45,45,45,45,45,45,45,45,45,45,45,20,
                    18,45,45,45,45,45,45,45,45,45,45,45,45,45,45,20,
                    18,45,45,45,45,45,45,45,45,45,45,45,45,45,45,20,
                    18,45,45,154,155,45,45,45,45,45,45,45,45,45,45,20,
                    18,45,45,44,44,45,45,148,149,45,45,60,61,45,45,20,
                    18,45,45,45,45,45,45,44,44,45,45,149,148,149,149,20,
                    18,45,45,45,45,45,45,45,45,45,149,165,44,44,44,20,
                    18,45,45,45,148,149,45,45,45,149,165,44,45,45,45,20,
                    18,26,45,45,44,44,45,149,148,165,44,45,45,45,45,20,
                    18,44,61,45,45,45,45,44,44,44,45,45,45,45,45,20,
                    18,22,23,22,23,45,45,45,45,45,45,45,45,45,45,20,
                    18,44,44,44,39,22,23,45,23,22,45,45,45,45,45,20,
                    18,45,45,45,44,44,44,45,44,44,45,26,45,45,45,20,
                    18,60,61,45,45,45,60,61,45,45,45,44,45,60,61,20,
                    160,161,160,161,160,161,160,161,160,161,160,161,160,161,160,161,
                    176,177,176,177,176,177,176,177,176,177,176,177,176,177,176,177,
                    162,163,162,163,162,163,162,163,162,163,162,163,162,163,162,163
                },
                {
                    new CollisionBox(
                        ZERO_VEC3,
                        1.f  * TILE_SIZE,
                        19.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(15.f * TILE_SIZE, 0.f, 0.f),
                        1.f  * TILE_SIZE,
                        19.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(0.f, 12.f * TILE_SIZE, 0.f),
                        5.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(4.f * TILE_SIZE, 13.f * TILE_SIZE, 0.f),
                        3.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(8.f * TILE_SIZE, 13.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(11.f * TILE_SIZE, 14.f * TILE_SIZE, 0.f),
                        1.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(1.f * TILE_SIZE, 10.f * TILE_SIZE, 0.f),
                        1.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(4.f * TILE_SIZE, 9.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(7.f * TILE_SIZE, 6.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    win_collision,
                    new CollisionBox(
                        glm::vec3(11.f * TILE_SIZE, 7.f * TILE_SIZE, 0.f),
                        4.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(10.f * TILE_SIZE, 8.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(9.f * TILE_SIZE, 9.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(7.f * TILE_SIZE, 10.f * TILE_SIZE, 0.f),
                        3.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(0.f, 16.f * TILE_SIZE, 0.f),
                        20.f  * TILE_SIZE,
                        3.f * TILE_SIZE
                    )
                },
                win_collision
            );

            m_game_state.enemy = new EnemyEntity(
                10.f,
                10.f,
                load_texture(ENEMY_B_FILEPATH),
                SCARED_CHASE 
            );
        }
        
        void initialise() override
        {
            // ————— GAME STATE ————— //
            m_game_state.scene_index = 4;

            // ————— RENDERING ————— //
            glClearColor(
                136.0f / 255.0f, 
                112.0f / 255.0f,
                0.f,
                1.0f
            );

            LevelScene::initialise();
        }
};

#endif

