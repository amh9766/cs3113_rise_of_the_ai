#ifndef ENDING_SCREEN_H
#define ENDING_SCREEN_H

#include "ScreenScene.h"
#include "platformer_lib.h"
#include "helper.h"

class EndingScreen : public ScreenScene
{
    public:
        EndingScreen(int next_scene_index)
            : ScreenScene(next_scene_index)
        {
            m_game_state.bgm = Mix_LoadMUS(ALL_STAGE_CLEAR_BGM_FILEPATH);

            m_game_state.background = new Background(
                INTERNAL_HEIGHT,
                INTERNAL_WIDTH,
                load_texture(ENDING_FILEPATH)
            );
        }
        
        void initialise() override 
        { 
            m_game_state.scene_index = 2;

            Mix_PlayMusic(m_game_state.bgm, 1);
            Mix_VolumeMusic(MIX_MAX_VOLUME / 3);

            ScreenScene::initialise();
        }
};

#endif
