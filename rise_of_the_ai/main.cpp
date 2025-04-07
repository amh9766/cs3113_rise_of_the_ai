/**
* Author: Amani Hernandez (amh9766)
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
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
#include <ctime>

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Scene.h"
#include "LevelScene.h"
#include "helper.h"
#include "platformer_lib.h"
#include "cmath"

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

Scene* g_current_scene = nullptr;

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

    g_current_scene = new LevelScene();
    g_current_scene->initialise();
        
    // ————— GENERAL ————— //
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
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
                        default:
                            g_current_scene->process_key_down(event);
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
                            g_current_scene->process_key_up(event);
                            break;
                    }
                }
                break;
            default:
                break;
        }
    }

    g_current_scene->process_key_state(SDL_GetKeyboardState(NULL));
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
        g_current_scene->update(FIXED_TIMESTEP);
        delta_time -= FIXED_TIMESTEP;
    }

    g_time_accumulator = delta_time;
}

void render()
{
    // ————— GENERAL ————— //
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableVertexAttribArray(g_shader_program.get_position_attribute());
    glEnableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());

    // ————— SCENE ————— //
    g_current_scene->render(&g_shader_program);
    
    // ————— GENERAL ————— //
    glDisableVertexAttribArray(g_shader_program.get_position_attribute());
    glDisableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());

    SDL_GL_SwapWindow(g_display_window);
}

void shutdown() 
{
    delete g_current_scene;
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
