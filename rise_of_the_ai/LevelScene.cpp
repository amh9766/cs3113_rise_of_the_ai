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

#include "LevelScene.h"
#include "platformer_lib.h"
#include "helper.h"

LevelScene::~LevelScene()
{
    delete m_game_state.player;

    delete m_game_state.map;

    delete m_game_state.mission_won;
    delete m_game_state.mission_loss;

    Mix_FreeMusic(m_game_state.bgm);
}

void LevelScene::initialise()
{
    // ————— BACKGROUND ————— //
    m_game_state.mission_won = new Background(
        INTERNAL_HEIGHT,
        INTERNAL_WIDTH,
        load_texture(MISSION_WON_FILEPATH)
    );

    m_game_state.mission_loss = new Background(
        INTERNAL_HEIGHT,
        INTERNAL_WIDTH,
        load_texture(MISSION_LOSS_FILEPATH)
    );

    m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    // ————— MAP ————— //
    m_game_state.map = new Map(
        3,
        5,
        load_texture(TILESET_FILEPATH),
        {
            { 1, -0.5f }, { 1, -0.5f }, { 1, -0.5f },
            { 1, -0.5f }, { 1, -0.5f }, { 1, -0.5f },
            { 1, -0.5f }, { 1, -0.5f }, { 1, -0.5f },
            { 1, -0.5f }, { 1, -0.5f }, { 1, -0.5f },
            { 16, 0.5f }, { 17, 0.5f }, { 16, 0.5f }
        }
    );

    // ————— PLAYER ————— //
    m_game_state.player = new PlayerEntity(
        24.0f,
        20.0f,
        load_texture(PLAYER_FILEPATH),
        { 
            { 8, 0 }, // Idle
            { 5, 1 }, // Up
            { 5, 1 }, // Down
            { 4, 0 }  // Horizontal
        },
        8
    );

    // ————— PLATFORMS ————— //
    
    // ————— UI ————— //
}

void LevelScene::process_key_down(SDL_Event& event)
{
    switch (event.key.keysym.sym) {
        default:
            break;
    }
}

void LevelScene::process_key_state(const Uint8* key_state)
{
    // Reset any input-based forces
    m_game_state.player->start_neutral();

    if (key_state[SDL_SCANCODE_LEFT])  m_game_state.player->push_left();
    if (key_state[SDL_SCANCODE_RIGHT]) m_game_state.player->push_right();
    if (key_state[SDL_SCANCODE_UP])    m_game_state.player->push_up();
    if (key_state[SDL_SCANCODE_DOWN])  m_game_state.player->push_down();
}

void LevelScene::update(float delta_time)
{
    std::vector<PlatformEntity> platforms;
    m_game_state.player->update(delta_time, platforms);

}

void LevelScene::render(ShaderProgram* program)
{
    // ————— MAP ————— //
    m_game_state.map->render(program);

    // ————— PLAYER ————— //
    m_game_state.player->render(program);

    // ————— PLATFORM ————— //
}
