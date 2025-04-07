/**
* Author: Amani Hernandez (amh9766)
* Assignment: Lunar Lander
* Date due: 2025-3-18, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#define STB_IMAGE_IMPLEMENTATION
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
#include "stb_image.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Entity.h"
#include "AnimationInfo.h"
#include "AnimatedEntity.h"
#include "PlayerEntity.h"
#include "PlatformEntity.h"
#include "Background.h"
#include "UILabel.h"
#include "helper.h"
#include "lunar_lib.h"

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
                MISSION_LOSS_FILEPATH[] = "content/mission_loss.png";

constexpr GLint NUMBER_OF_TEXTURES = 1;
constexpr GLint LEVEL_OF_DETAIL    = 0;
constexpr GLint TEXTURE_BORDER     = 0;

constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// ————— STRUCTS AND ENUMS —————//
enum AppStatus { RUNNING, TERMINATED };

struct GameState
{
    PlayerEntity* player;
    UILabel* fuel_label;

    Background* background;
    Background* mission_won;
    Background* mission_loss;

    std::vector<PlatformEntity> platforms;
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
GLuint load_texture(const char* filepath);

void initialise();
void process_input();
void update();
void render();
void shutdown();

GLuint load_texture(const char* filepath)
{
    int width, height, number_of_components;
    unsigned char* image = stbi_load(filepath, &width, &height, &number_of_components, 
                                     STBI_rgb_alpha);

    if (image == NULL)
    {
        LOG("Unable to load image. Make sure the path is correct.");
        assert(false);
    }

    GLuint textureID;
    glGenTextures(NUMBER_OF_TEXTURES, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, LEVEL_OF_DETAIL, GL_RGBA, width, height, TEXTURE_BORDER, 
                 GL_RGBA, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(image);

    return textureID;
}

void initialise()
{
    SDL_Init(SDL_INIT_VIDEO);
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
    g_game_state.background = new Background(
        INTERNAL_HEIGHT,
        INTERNAL_WIDTH,
        load_texture(BACKGROUND_FILEPATH)
    );

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
    GLuint platform_tex_id = load_texture(PLATFORM_FILEPATH);
    g_game_state.platforms.emplace_back(
        glm::vec3(204.0f, 45.0f, 0.0f),
        64.0f,
        32.0f,
        10.0f,
        8.0f,
        platform_tex_id
    );
    g_game_state.platforms.emplace_back(
        glm::vec3(92.0f, 194.0f, 0.0f),
        64.0f,
        32.0f,
        10.0f,
        8.0f,
        platform_tex_id
    );
    g_game_state.platforms.emplace_back(
        glm::vec3(342.0f, 245.0f, 0.0f),
        64.0f,
        32.0f,
        10.0f,
        8.0f,
        platform_tex_id
    );

    g_game_state.platforms[2].set_dynamic();

    // ————— UI ————— //
    GLuint alphanum_tex_id = load_texture(ALPHANUM_FILEPATH);
    g_game_state.fuel_label = new UILabel(
        glm::vec3(0.0f),
        glm::vec3(12.0f, 14.0f, 0.0f),
        alphanum_tex_id,
        "FUEL",
        4
    );

    // ————— GENERAL ————— //
    glEnable(GL_BLEND);
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

            for (int i = 0; i < g_game_state.platforms.size(); i++)
                g_game_state.platforms[i].update(delta_time);

            g_game_state.player->update(FIXED_TIMESTEP, g_game_state.platforms);
            g_game_state.fuel_label->update(g_game_state.player->get_fuel());

            if (g_won || g_lost) break;

            delta_time -= FIXED_TIMESTEP;
        }

        g_time_accumulator = delta_time;
    }
}

void render()
{
    // ————— GENERAL ————— //
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(g_shader_program.get_position_attribute());
    glEnableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());

    g_game_state.background->render(&g_shader_program);

    // ————— PLAYER ————— //
    g_game_state.player->render(&g_shader_program);

    for (int i = 0; i < g_game_state.platforms.size(); i++)
        g_game_state.platforms[i].render(&g_shader_program);

    // ————— PLATFORM ————— //
    g_game_state.fuel_label->render(&g_shader_program);

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
    delete g_game_state.fuel_label;

    delete g_game_state.background;
    delete g_game_state.mission_won;
    delete g_game_state.mission_loss;

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
