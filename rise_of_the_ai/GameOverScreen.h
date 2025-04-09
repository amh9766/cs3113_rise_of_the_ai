#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "ScreenScene.h"
#include "platformer_lib.h"
#include "helper.h"

class GameOverScreen : public ScreenScene
{
    public:
        GameOverScreen(int next_scene_index)
            : ScreenScene(next_scene_index)
        {
            m_game_state.bgm = Mix_LoadMUS(GAME_OVER_BGM_FILEPATH);

            m_game_state.background = new Background(
                INTERNAL_HEIGHT,
                INTERNAL_WIDTH,
                load_texture(GAME_OVER_FILEPATH)
            );
        }
        
        void initialise() override 
        { 
            m_game_state.scene_index = 1;

            Mix_HaltChannel(-1);
            Mix_PlayMusic(m_game_state.bgm, 1);
            Mix_VolumeMusic(MIX_MAX_VOLUME / 3);

            ScreenScene::initialise();
        }
};

#endif
