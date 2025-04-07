#ifndef PLATFORMER_LIB_H
#define PLATFORMER_LIB_H

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

constexpr int TILE_SIZE = 16;

constexpr int TILESET_WIDTH  = 16,
              TILESET_HEIGHT = 12;

constexpr float TILESET_U = 1.0f / (float) TILESET_WIDTH,
                TILESET_V = 1.0f / (float) TILESET_HEIGHT;

#endif
