#ifndef LEVEL_C_H
#define LEVEL_C_H

#include <SDL.h>
#include <SDL_mixer.h>

#include "LevelScene.h"
#include "CollisionBox.h"
#include "Map.h"
#include "platformer_lib.h"
#include "helper.h"

class LevelC : public LevelScene
{
    public:
        LevelC(int next_scene_index, PlayerEntity* player, GLuint texture_id)
            : LevelScene(next_scene_index, player)
        {
            m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);

            // ————— MAP ————— //
            CollisionBox* win_collision = new CollisionBox(
                glm::vec3(27.f * TILE_SIZE, 7.f * TILE_SIZE, 0.f),
                2.f * TILE_SIZE,
                1.f * TILE_SIZE
            );
            m_game_state.map = new Map(
                30,
                32,
                BOTH,
                texture_id,
                glm::vec3(3.f * TILE_SIZE, 27.f * TILE_SIZE, 0.f),
                glm::vec3(0.f * TILE_SIZE, 40.f * TILE_SIZE, 0.f),
                {
                    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,95,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,95,
                    -1,-1,-1,-1,-1,-1,-1,-1,-1,95,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,95,-1,-1,-1,-1,-1,95,-1,-1,
                    -1,-1,95,-1,-1,-1,95,-1,95,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,95,-1,-1,
                    95,-1,-1,-1,-1,-1,-1,95,-1,-1,-1,-1,-1,-1,-1,-1,95,-1,-1,-1,-1,-1,-1,95,-1,-1,95,95,95,-1,
                    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,95,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,95,-1,-1,
                    -1,95,-1,-1,-1,95,-1,-1,-1,95,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,95,-1,-1,-1,-1,-1,-1,-1,-1,
                    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,95,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                    37,19,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,154,155,-1,
                    53,37,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,95,-1,-1,-1,95,-1,-1,-1,-1,-1,-1,95,-1,48,49,49,50,
                    69,37,20,-1,-1,-1,-1,95,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,51,51,51,51,
                    37,37,20,-1,95,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,51,-1,-1,67,67,67,67,
                    37,37,20,-1,-1,-1,-1,-1,-1,18,19,20,-1,-1,-1,-1,-1,-1,-1,-1,51,95,-1,67,-1,-1,67,66,67,67,
                    37,37,20,-1,-1,-1,-1,-1,-1,18,37,87,78,95,-1,18,19,20,-1,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    86,87,86,87,88,88,95,88,86,86,87,88,94,-1,78,18,37,20,-1,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    87,47,88,88,58,59,88,89,88,88,88,89,94,78,94,18,37,20,-1,-1,66,-1,-1,67,-1,-1,67,67,66,67,
                    62,63,89,89,74,75,89,89,89,89,89,94,94,94,94,18,37,20,95,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    63,30,89,89,88,88,89,90,89,89,89,94,94,94,94,18,37,20,-1,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    87,47,89,90,89,89,89,88,89,89,89,94,94,94,94,18,37,20,-1,-1,67,-1,-1,66,-1,95,67,67,67,67,
                    63,30,89,87,89,89,94,86,90,87,87,87,94,94,94,18,37,20,-1,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    86,87,86,90,89,94,94,78,78,78,78,78,94,94,62,47,46,20,-1,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    15,47,86,87,94,94,94,94,94,94,94,94,94,62,62,62,47,20,-1,-1,66,-1,-1,67,-1,-1,67,66,67,67,
                    31,30,31,62,94,94,94,94,94,94,94,94,94,78,78,46,63,20,-1,-1,67,-1,95,67,-1,-1,67,67,67,67,
                    14,15,62,63,94,94,94,94,94,94,46,47,94,94,94,14,15,20,-1,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    30,62,63,78,94,94,94,94,94,94,78,78,46,94,94,46,31,20,-1,-1,67,-1,-1,66,-1,-1,67,67,67,67,
                    62,63,78,94,94,94,94,94,94,94,94,94,78,94,94,14,15,20,-1,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    46,63,94,94,94,94,94,94,94,94,94,94,94,94,62,63,46,20,-1,-1,67,95,-1,67,-1,-1,67,67,67,67,
                    30,47,94,94,94,94,94,94,94,94,94,94,94,94,78,14,15,20,-1,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    63,47,94,94,94,94,94,94,94,94,94,94,46,62,94,30,63,20,-1,-1,66,-1,-1,67,-1,95,67,67,66,67,
                    30,63,94,94,94,94,94,94,62,46,94,94,78,78,94,46,15,20,-1,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    63,47,94,94,62,47,94,94,78,78,94,94,94,94,94,30,31,20,-1,95,67,-1,-1,67,-1,-1,67,67,67,67,
                    47,46,62,46,46,62,94,94,94,94,94,94,94,94,94,63,46,20,-1,-1,67,-1,-1,67,-1,-1,67,67,67,67,
                    30,31,46,63,78,78,94,94,94,94,94,94,94,94,94,30,31,20,-1,-1,67,-1,-1,67,-1,-1,67,66,67,67
                },
                {
                    new CollisionBox(
                        ZERO_VEC3,
                        2.f  * TILE_SIZE,
                        32.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(2.f * TILE_SIZE, 7.f * TILE_SIZE, 0.f),
                        1.f  * TILE_SIZE,
                        17.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(3.f * TILE_SIZE, 10.f * TILE_SIZE, 0.f),
                        1.f  * TILE_SIZE,
                        10.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(4.f * TILE_SIZE, 29.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        2.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(4.f * TILE_SIZE, 14.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        2.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(15.f * TILE_SIZE, 12.f * TILE_SIZE, 0.f),
                        3.f  * TILE_SIZE,
                        20.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(8.f * TILE_SIZE, 28.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(10.f * TILE_SIZE, 22.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(12.f * TILE_SIZE, 27.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(14.f * TILE_SIZE, 25.f * TILE_SIZE, 0.f),
                        1.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(12.f * TILE_SIZE, 23.f * TILE_SIZE, 0.f),
                        1.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(14.f * TILE_SIZE, 19.f * TILE_SIZE, 0.f),
                        1.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(7.f * TILE_SIZE, 16.f * TILE_SIZE, 0.f),
                        1.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(7.f * TILE_SIZE, 18.f * TILE_SIZE, 0.f),
                        5.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(9.f * TILE_SIZE, 11.f * TILE_SIZE, 0.f),
                        3.f  * TILE_SIZE,
                        2.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(8.f * TILE_SIZE, 13.f * TILE_SIZE, 0.f),
                        3.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(23.f * TILE_SIZE, 9.f * TILE_SIZE, 0.f),
                        1.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(20.f * TILE_SIZE, 10.f * TILE_SIZE, 0.f),
                        1.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(13.f * TILE_SIZE, 20.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    ),
                    new CollisionBox(
                        glm::vec3(2.f * TILE_SIZE, 30.f * TILE_SIZE, 0.f),
                        2.f  * TILE_SIZE,
                        2.f * TILE_SIZE
                    ),
                    win_collision,
                    new CollisionBox(
                        glm::vec3(26.f * TILE_SIZE, 8.f * TILE_SIZE, 0.f),
                        4.f  * TILE_SIZE,
                        1.f * TILE_SIZE
                    )
                },
                win_collision
            );

            m_game_state.enemy = new EnemyEntity(
                16.f,
                16.f,
                load_texture(ENEMY_C_FILEPATH),
                STEP_CHASE
            );
        }
        
        void initialise() override
        {
            // ————— GAME STATE ————— //
            m_game_state.scene_index = 5;

            // ————— RENDERING ————— //
            glClearColor(
                0.f,
                0.f,
                0.f,
                1.0f
            );

            LevelScene::initialise();
        }
};

#endif

