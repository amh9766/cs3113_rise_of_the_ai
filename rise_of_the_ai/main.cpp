/**
* Author: Amani Hernandez (amh9766)
* Assignment: Lunar Lander
* Date due: 2025-3-18, 11:59pm
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
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Entity.h"
#include "AnimationInfo.h"
#include "AnimatedEntity.h"
#include "PlayerEntity.h"
#include "Map.h"
#include "PlatformEntity.h"
#include "Background.h"
#include "UILabel.h"
#include "helper.h"
#include "lunar_lib.h"
#include <SDL_mixer.h>

constexpr int CD_QUAL_FREQ    = 44100,  // compact disk (CD) quality frequency
          AUDIO_CHAN_AMT  = 2,
          AUDIO_BUFF_SIZE = 4096;

// ————— CONSTANTS ————— //
constexpr int WINDOW_WIDTH  = 960,
              WINDOW_HEIGHT = 640;

constexpr float BG_RED = 0.1922f,
                BG_BLUE = 0.549f,
                BG_GREEN = 0.9059f,
                BG_OPACITY = 1.0f;

constexpr int VIEWPORT_X = 0,
              VIEWPORT_Y = 0,
              VIEWPORT_WIDTH  = WINDOW_WIDTH,
              VIEWPORT_HEIGHT = WINDOW_HEIGHT;

constexpr char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
               F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

constexpr float MILLISECONDS_IN_SECOND = 1000.0;

// Sources:
//      Player     - https://www.spriters-resource.com/ds_dsi/kirbysqueaksquad/sheet/2505/
//      Background - https://www.spriters-resource.com/game_boy_advance/kirbynim/sheet/2976/
//      Platform   - https://www.spriters-resource.com/game_boy_advance/kirbynim/sheet/134385/
//      Font       - https://www.spriters-resource.com/ds_dsi/kirbysqueaksquad/sheet/3337/
constexpr char  PLAYER_FILEPATH[]       = "content/player.png",
                PLATFORM_FILEPATH[]     = "content/platform.png",
                ALPHANUM_FILEPATH[]     = "content/alphanum.png",
                BACKGROUND_FILEPATH[]   = "content/background.png",
                MISSION_WON_FILEPATH[]  = "content/mission_won.png",
                MISSION_LOSS_FILEPATH[] = "content/mission_loss.png",
                TILESET_FILEPATH[] = "content/tileset.png";

constexpr char BGM_FILEPATH[] = "content/music/wood_man.mp3";
constexpr int    LOOP_FOREVER = -1;

Mix_Music *g_music;

constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// ————— STRUCTS AND ENUMS —————//
enum AppStatus { RUNNING, TERMINATED };

struct GameState
{
    PlayerEntity* player;
    Map* map;

    Background* mission_won;
    Background* mission_loss;
};

// ————— VARIABLES ————— //
GameState g_game_state;

SDL_Window* g_display_window;
AppStatus g_app_status = RUNNING;

ShaderProgram g_shader_program = ShaderProgram();
glm::mat4 g_view_matrix, g_projection_matrix;

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

    g_display_window = SDL_CreateWindow("Lunar Lander",
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

    g_view_matrix       = IDENTITY_MAT;
    g_projection_matrix = glm::ortho(0.0f, INTERNAL_WIDTH, INTERNAL_HEIGHT, 0.0f, -1.0f, 1.0f);

    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);

    glUseProgram(g_shader_program.get_program_id());

    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);

    // ————— BACKGROUND ————— //
    g_game_state.mission_won = new Background(
        INTERNAL_HEIGHT,
        INTERNAL_WIDTH,
        load_texture(MISSION_WON_FILEPATH)
    );

    g_game_state.mission_loss = new Background(
        INTERNAL_HEIGHT,
        INTERNAL_WIDTH,
        load_texture(MISSION_LOSS_FILEPATH)
    );

    g_music = Mix_LoadMUS(BGM_FILEPATH);

    Mix_PlayMusic(g_music, LOOP_FOREVER);

    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    // ————— MAP ————— //
    g_game_state.map = new Map(
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
    g_game_state.player = new PlayerEntity(
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
    
    // ————— GENERAL ————— //
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void process_input()
{
    // Reset any input-based forces
    g_game_state.player->start_neutral();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
            // End game
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            g_app_status = TERMINATED;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_q:
                // Quit the game with a keystroke
                g_app_status = TERMINATED;
                break;
            case SDLK_RETURN:
                if (g_won || g_lost) 
                {
                    g_game_state.player->reset();
                    g_won = false;
                    g_lost = false;
                }
                else g_pause = !g_pause;
                break;
            default:
                break;
            }

        default:
            break;
        }
    }

    const Uint8* key_state = SDL_GetKeyboardState(NULL);

    if (key_state[SDL_SCANCODE_LEFT])  g_game_state.player->push_left();
    if (key_state[SDL_SCANCODE_RIGHT]) g_game_state.player->push_right();
    if (key_state[SDL_SCANCODE_UP])    g_game_state.player->push_up();
    if (key_state[SDL_SCANCODE_DOWN])  g_game_state.player->push_down();
}

void update()
{
    // ————— DELTA TIME ————— //
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;

    if (!(g_won || g_lost) && !g_pause)
    {
        // ————— FIXED TIMESTEP ————— //
        delta_time += g_time_accumulator;

        if (delta_time < FIXED_TIMESTEP)
        {
            g_time_accumulator = delta_time;
            return;
        }

        while (delta_time >= FIXED_TIMESTEP)
        {
            g_won  = g_game_state.player->get_collide_bottom();
            g_lost = g_game_state.player->is_out_of_bounds();
            
            std::vector<PlatformEntity> platforms;
            g_game_state.player->update(delta_time, platforms);

            if (g_won || g_lost) break;

            delta_time -= FIXED_TIMESTEP;
        }

        g_time_accumulator = delta_time;
    }
}

void render()
{
    // ————— GENERAL ————— //
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableVertexAttribArray(g_shader_program.get_position_attribute());
    glEnableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());

    // ————— MAP ————— //
    g_game_state.map->render(&g_shader_program);

    // ————— PLAYER ————— //
    g_game_state.player->render(&g_shader_program);

    // ————— PLATFORM ————— //
    if      (g_won)  g_game_state.mission_won->render(&g_shader_program);
    else if (g_lost) g_game_state.mission_loss->render(&g_shader_program);

    // ————— GENERAL ————— //
    glDisableVertexAttribArray(g_shader_program.get_position_attribute());
    glDisableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());

    SDL_GL_SwapWindow(g_display_window);
}

void shutdown() 
{
    delete g_game_state.player;

    delete g_game_state.mission_won;
    delete g_game_state.mission_loss;
    
    delete g_game_state.map;

    Mix_FreeMusic(g_music);
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
