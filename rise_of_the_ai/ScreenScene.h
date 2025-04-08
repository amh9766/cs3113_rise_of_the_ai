#ifndef SCREEN_SCENE_H 
#define SCREEN_SCENE_H 

#include <SDL.h>
#include "Scene.h"

class ScreenScene : public Scene
{
    private:
        Mix_Chunk* m_press_sfx;

    public:
       ScreenScene(int next_scene_index);
       ~ScreenScene();

       void initialise() override;
       void process_key_down(SDL_Event& event) override;
       void process_key_up(SDL_Event& event) override { }
       void process_key_state(const Uint8* key_state) override { }
       void update(float delta_time) override { }
       void render(ShaderProgram* program) override;
};

#endif
