#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include <SDL.h>
#include "Scene.h"
#include "PlayerEntity.h"
#include "platformer_lib.h"

class LevelScene : public Scene
{
    private:
        GLuint m_texture_id;

    public:
        LevelScene(PlayerEntity* player, GLuint m_texture_id);
        ~LevelScene();

        void initialise() override;
        void process_key_down(SDL_Event& event) override;
        void process_key_up(SDL_Event& event) override;
        void process_key_state(const Uint8* key_state) override;
        void update(float delta_time) override;
        void render(ShaderProgram* program) override;
};

#endif
