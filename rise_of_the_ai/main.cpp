/**
* Author: Amani Hernandez (amh9766)
* Assignment: Rise of the AI
* Date due: 2025-04-07, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES 1

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include <vector>
#include <ctime>

#include "cmath"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Scene.h"

// Game-specific
#include "StartScreen.h"
#include "GameOverScreen.h"
#include "EndingScreen.h"
#include "LevelA.h"
#include "LevelB.h"
#include "LevelC.h"
#include "platformer_lib.h"

#include "helper.h"

// ————— CONSTANTS ————— //
constexpr int CD_QUAL_FREQ    = 44100,  // compact disk (CD) quality frequency
              AUDIO_CHAN_AMT  = 2,
              AUDIO_BUFF_SIZE = 4096;

constexpr int WINDOW_WIDTH  = 768,
              WINDOW_HEIGHT = 672;

constexpr int VIEWPORT_X = 0,
              VIEWPORT_Y = 0,
              VIEWPORT_WIDTH  = WINDOW_WIDTH,
              VIEWPORT_HEIGHT = WINDOW_HEIGHT;

constexpr char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
               F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

constexpr float MILLISECONDS_IN_SECOND = 1000.0;

// ————— STRUCTS AND ENUMS —————//
enum AppStatus { RUNNING, TERMINATED };

// ————— VARIABLES ————— //
SDL_Window* g_display_window;
AppStatus g_app_status = RUNNING;

ShaderProgram g_shader_program = ShaderProgram();
glm::mat4 g_view_matrix, g_projection_matrix;

PlayerEntity* g_player = nullptr;

// ———— SCENES ———— //
std::vector<Scene*> g_scenes;
int g_scene_index;
void switch_scene(int scene_index)
{
    g_scene_index = scene_index;
    g_scenes[g_scene_index]->initialise();
}

float g_previous_ticks   = 0.0f;
float g_time_accumulator = 0.0f;

bool g_pause = false,
     g_won = false,
     g_lost = false;

// ———— GENERAL FUNCTIONS ———— //
void initialise();
void process_input();
void update();
void render();
void shutdown();

void initialise()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    Mix_OpenAudio(
        CD_QUAL_FREQ,        // the frequency to playback audio at (in Hz)
        MIX_DEFAULT_FORMAT,  // audio format
        AUDIO_CHAN_AMT,      // number of channels (1 is mono, 2 is stereo, etc).
        AUDIO_BUFF_SIZE      // audio buffer size in sample FRAMES (total samples divided by channel count)
    );

    g_display_window = SDL_CreateWindow("Rise of the AI",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    
    if (context == nullptr)
    {
        LOG("ERROR: Could not create OpenGL context.\n");
        shutdown();
    }

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);

    g_projection_matrix = glm::ortho(0.0f, INTERNAL_WIDTH, INTERNAL_HEIGHT, 0.0f, -1.0f, 1.0f);

    g_shader_program.set_projection_matrix(g_projection_matrix);
    glUseProgram(g_shader_program.get_program_id());

    // Set up player
    g_player = new PlayerEntity(
        load_texture(PLAYER_FILEPATH),
        { 
            { 1, -1, BLINK, 75 * FIXED_TIMESTEP }, // Idle
            { 1, -1, IDLE, 10 * FIXED_TIMESTEP },   // Blink
            { 1, -1, WALK, 10 * FIXED_TIMESTEP },   // Inch
            { 4, 0,  NONE, 7 * FIXED_TIMESTEP },   // Walk
            { 1, 0,  NONE, 1 * FIXED_TIMESTEP },    // Jump 
            { 1, 0,  NONE, 1 * FIXED_TIMESTEP }     // Hurt 
        },
        4
    );

    GLuint tileset_texture_id = load_texture(TILESET_FILEPATH);

    g_scenes.push_back(new StartScreen(3));
    g_scenes.push_back(new GameOverScreen(0));
    g_scenes.push_back(new EndingScreen(0));
    g_scenes.push_back(new LevelA(4, g_player, tileset_texture_id));
    g_scenes.push_back(new LevelB(5, g_player, tileset_texture_id));
    g_scenes.push_back(new LevelC(2, g_player, tileset_texture_id));

    g_scene_index = 0;
    g_scenes[g_scene_index]->initialise();
        
    // ————— GENERAL ————— //
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void process_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_app_status = TERMINATED;
                break;
            case SDL_KEYDOWN:
                if (event.key.repeat == 0)
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_q:
                            g_app_status = TERMINATED;
                            break;
                        case SDLK_1:
                            switch_scene(0);
                            break;
                        case SDLK_2:
                            switch_scene(1);
                            break;
                        case SDLK_3:
                            switch_scene(2);
                            break;
                        case SDLK_4:
                            switch_scene(3);
                            break;
                        case SDLK_5:
                            switch_scene(4);
                            break;
                        case SDLK_6:
                            switch_scene(5);
                            break;
                        default:
                            g_scenes[g_scene_index]->process_key_down(event);
                            break;
                    }
                }
                break;
            case SDL_KEYUP:
                if (event.key.repeat == 0)
                {
                    switch (event.key.keysym.sym)
                    {
                        default:
                            g_scenes[g_scene_index]->process_key_up(event);
                            break;
                    }
                }
                break;
            default:
                break;
        }
    }

    g_scenes[g_scene_index]->process_key_state(SDL_GetKeyboardState(NULL));
}

void update()
{
    // ————— DELTA TIME ————— //
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;

    // ————— FIXED TIMESTEP ————— //
    delta_time += g_time_accumulator;

    if (delta_time < FIXED_TIMESTEP)
    {
        g_time_accumulator = delta_time;
        return;
    }

    while (delta_time >= FIXED_TIMESTEP)
    {
        // Check if the scene has changed
        int scene_index = g_scenes[g_scene_index]->get_scene_index();
        if (g_scene_index != scene_index) switch_scene(scene_index);

        // Apply scene update
        g_scenes[g_scene_index]->update(FIXED_TIMESTEP);
        delta_time -= FIXED_TIMESTEP;
    }

    g_time_accumulator = delta_time;
}

void render()
{
    // ————— GENERAL ————— //
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(g_shader_program.get_position_attribute());
    glEnableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());

    // ————— SCENE ————— //
    g_scenes[g_scene_index]->render(&g_shader_program);
    
    // ————— GENERAL ————— //
    glDisableVertexAttribArray(g_shader_program.get_position_attribute());
    glDisableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());

    SDL_GL_SwapWindow(g_display_window);
}

void shutdown() 
{
    for (int i = 0; i < g_scenes.size(); i++)
    {
        delete g_scenes[i];
    }
    delete g_player;

    SDL_Quit();
}



int main(int argc, char* argv[])
{
    initialise();

    while (g_app_status == RUNNING)
    {
        process_input();
        update();
        render();
    }

    shutdown();
    return 0;
}
