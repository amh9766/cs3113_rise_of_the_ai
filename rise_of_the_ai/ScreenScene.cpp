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

#include "ScreenScene.h"
#include "platformer_lib.h"
#include "helper.h"

ScreenScene::ScreenScene()
{
    m_game_state.background = new Background(
        INTERNAL_HEIGHT,
        INTERNAL_WIDTH,
        load_texture(START_FILEPATH)
    );
}

ScreenScene::~ScreenScene()
{
    delete m_game_state.background;
    //Mix_FreeMusic(m_game_state.bgm);
}

void ScreenScene::initialise()
{
    // ————— GAME STATE ————— //
    m_game_state.scene_index = 0;

    // ————— RENDERING ————— //
    glClearColor(
        0.f, 
        0.f, 
        0.f, 
        1.0f
    );

    m_game_state.view_matrix = IDENTITY_MAT;
    
    //m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    //Mix_PlayMusic(m_game_state.bgm, -1);
    //Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}

void ScreenScene::process_key_down(SDL_Event& event)
{
    switch (event.key.keysym.sym) {
        case SDLK_RETURN:
            m_game_state.scene_index = 1;
            break;
        default:
            break;
    }
}

void ScreenScene::render(ShaderProgram* program)
{
    // ————— CAMERA ————— //
    program->set_view_matrix(m_game_state.view_matrix);

    // ————— BACKGROUND ————— //
    m_game_state.background->render(program);
}
