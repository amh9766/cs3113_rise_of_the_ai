/**
* Author: Amani Hernandez (amh9766)
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include <vector>

#include "glm/gtc/matrix_transform.hpp"
#include "LevelScene.h"
#include "CollisionBox.h"
#include "Map.h"
#include "platformer_lib.h"
#include "helper.h"

LevelScene::LevelScene(PlayerEntity* player, GLuint texture_id)
    : m_texture_id(texture_id)
{
    m_game_state.player = player;

    m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    // ————— MAP ————— //
    m_game_state.map = new Map(
        35,
        14,
        HORIZONTAL,
        texture_id,
        glm::vec3(128.f, 0.f, 0.f),
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
            ),
            new CollisionBox(
                glm::vec3(23.f * TILE_SIZE, 4.f * TILE_SIZE, 0.f),
                2.f * TILE_SIZE,
                1.f * TILE_SIZE
            )
        }
    );
}

LevelScene::~LevelScene()
{
    delete m_game_state.map;

    Mix_FreeMusic(m_game_state.bgm);
}

void LevelScene::initialise()
{
    // ————— GAME STATE ————— //
    m_game_state.scene_index = 1;

    // ————— RENDERING ————— //
    glClearColor(
        24.0f / 255.0f, 
        60.0f / 255.0f,
        92.0f / 255.0f, 
        1.0f
    );
    
    // ————— PLAYER ————— //
    m_game_state.player->spawn(m_game_state.map->get_spawn_point());
}

void LevelScene::process_key_down(SDL_Event& event)
{
    switch (event.key.keysym.sym) {
        case SDLK_c:
            m_game_state.player->jump();
            break;
        default:
            break;
    }
}

void LevelScene::process_key_up(SDL_Event& event)
{
    switch (event.key.keysym.sym) {
        case SDLK_c:
            m_game_state.player->fall();
            break;
        default:
            break;
    }
}

void LevelScene::process_key_state(const Uint8* key_state)
{
    // Reset any input-based movements 
    m_game_state.player->start_neutral();

    if (key_state[SDL_SCANCODE_A]) m_game_state.player->move_left();
    if (key_state[SDL_SCANCODE_D]) m_game_state.player->move_right();
}

void LevelScene::update(float delta_time)
{
    // ————— PLAYER ————— //
    m_game_state.player->update(delta_time, m_game_state.map);

    // ————— CAMERA ————— //
    glm::vec3 player_position = m_game_state.player->get_position();
    glm::vec3 camera_position = ZERO_VEC3;
    if (m_game_state.map->does_scroll_horizontal())
    {
        float current_position = -player_position.x 
            + (INTERNAL_WIDTH - m_game_state.player->get_width()) / 2;
        float camera_max = -m_game_state.map->get_width() * TILE_SIZE 
            + INTERNAL_WIDTH;

        if (current_position < 0) 
        {
            if (current_position < camera_max) camera_position.x = camera_max;
            else camera_position.x = current_position;
        }
    }
    if (m_game_state.map->does_scroll_vertical())
    {
        float current_position = -player_position.y
            + (INTERNAL_HEIGHT - m_game_state.player->get_height()) / 2;
        float camera_max = -m_game_state.map->get_height() * TILE_SIZE
            + INTERNAL_HEIGHT;

        if (current_position < 0) 
        {
            if (current_position < camera_max) camera_position.y = camera_max;
            else camera_position.y = current_position;
        }
    }
    m_game_state.view_matrix = glm::translate(IDENTITY_MAT, camera_position);
}

void LevelScene::render(ShaderProgram* program)
{
    // ————— CAMERA ————— //
    program->set_view_matrix(m_game_state.view_matrix);

    // ————— MAP ————— //
    m_game_state.map->render(program);

    // ————— PLAYER ————— //
    m_game_state.player->render(program);
}
