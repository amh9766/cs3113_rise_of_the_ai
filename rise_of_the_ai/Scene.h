#ifndef SCENE_H
#define SCENE_H

#include "GameState.h"

class Scene
{
    protected:
        GameState m_game_state;
        int m_next_scene_index;

    public:
        Scene(int next_scene_index) : m_next_scene_index(next_scene_index) { }
        virtual ~Scene() { }

        virtual void initialise() = 0;
        virtual void process_key_down(SDL_Event& event) = 0;
        virtual void process_key_up(SDL_Event& event) = 0;
        virtual void process_key_state(const Uint8* key_state) = 0;
        virtual void update(float delta_time) = 0;
        virtual void render(ShaderProgram* program) = 0;

        int get_scene_index() const { return m_game_state.scene_index; }
        GameState const get_state() const { return m_game_state; }
};

#endif
