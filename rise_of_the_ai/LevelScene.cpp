/**
* Author: Amani Hernandez (amh9766)
* Assignment: Rise of the AI
* Date due: 2025-04-07, 11:59pm
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
#include "EnemyEntity.h"
#include "platformer_lib.h"
#include "helper.h"

LevelScene::LevelScene(int next_scene_index, PlayerEntity* player)
    : Scene(next_scene_index), m_pause(false)
{
    m_game_state.player = player;

    m_pause_sfx = Mix_LoadWAV(PAUSE_FILEPATH);
}

LevelScene::~LevelScene()
{
    delete m_game_state.map;
    delete m_game_state.enemy;
    Mix_FreeChunk(m_pause_sfx);
}

void LevelScene::initialise()
{
    // ————— PLAYER ————— //
    m_game_state.player->spawn(m_game_state.map->get_player_spawn_point());
    
    // ————— ENEMY ————— //
    m_game_state.enemy->spawn(m_game_state.map->get_enemy_spawn_point());
}

void LevelScene::process_key_down(SDL_Event& event)
{
    switch (event.key.keysym.sym) {
        case SDLK_RETURN:
            m_pause = !m_pause;
            Mix_PlayChannel(-1, m_pause_sfx, 0);
            Mix_VolumeChunk(m_pause_sfx, MIX_MAX_VOLUME / 4);
            break;
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
    if (m_pause) return;

    if (m_game_state.player->get_lives() <= 0) 
    {
        m_game_state.scene_index = 1;
        return;
    }

    // ————— ENEMY ————— //
    m_game_state.enemy->update(delta_time, m_game_state.player);

    // ————— PLAYER ————— //
    m_game_state.player->update(delta_time, m_game_state.map, m_game_state.enemy);

    if (m_game_state.map->get_win_collision()->get_collide_top())
    {
        m_game_state.scene_index = m_next_scene_index;
        return;
    }

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

    // ————— ENEMY ————— //
    m_game_state.enemy->render(program);

    // ————— PLAYER ————— //
    m_game_state.player->render(program);
}
