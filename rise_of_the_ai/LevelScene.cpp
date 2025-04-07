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
    glClearColor(
        24.0f / 255.0f, 
        60.0f / 255.0f,
        92.0f / 255.0f, 
        1.0f
    );

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
        29,
        14,
        load_texture(TILESET_FILEPATH),
        {
            -1,-1,81,82,-1,-1,-1,4,5,5,5,5,6,-1,-1,-1,4,5,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,96,97,98,-1,-1,-1,-1,-1,-1,-1,-1,4,5,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,112,113,114,115,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,5,5,6,-1,-1,-1,-1,-1,-1,-1,
            18,19,19,19,19,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            18,37,52,53,37,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            18,37,68,69,37,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            18,37,37,37,37,20,65,65,65,65,-1,-1,-1,-1,-1,-1,-1,48,49,49,50,-1,-1,-1,-1,-1,-1,-1,-1,
            18,37,37,37,37,20,64,64,64,64,-1,-1,-1,-1,-1,-1,-1,51,51,51,51,-1,-1,-1,-1,-1,-1,-1,-1,
            18,37,37,37,37,20,64,64,64,64,-1,-1,-1,-1,-1,-1,-1,67,66,67,67,-1,-1,-1,48,49,50,-1,-1,
            18,37,37,37,37,20,64,64,64,64,-1,-1,-1,-1,-1,-1,-1,67,67,66,67,-1,-1,-1,51,51,51,-1,-1,
            18,37,37,37,37,20,80,64,64,64,-1,-1,-1,-1,-1,-1,-1,66,67,67,67,-1,-1,-1,67,66,67,-1,-1,
            32,33,32,33,32,33,16,17,16,17,16,17,16,17,16,17,16,17,16,17,16,17,16,17,16,17,16,17,16,
            32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,
            32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32
        }
    );

    // ————— PLAYER ————— //
    m_game_state.player = new PlayerEntity(
        27.0f,
        30.0f,
        load_texture(PLAYER_FILEPATH),
        { 
            { 1, -1, BLINK, 125 * FIXED_TIMESTEP }, // Idle
            { 1, -1, IDLE, 10 * FIXED_TIMESTEP },   // Blink
            { 1, -1, WALK, 10 * FIXED_TIMESTEP },   // Inch
            { 4, 0,  NONE, 12 * FIXED_TIMESTEP },   // Walk
            { 1, 0,  NONE, FIXED_TIMESTEP },        // Jump 
            { 1, 0,  NONE, FIXED_TIMESTEP }         // Hurt 
        },
        4
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
