#ifndef GAME_ENGINE_DATA_HPP
#define GAME_ENGINE_DATA_HPP

#ifndef __WINDOW_BASE_WIDTH
    #define __WINDOW_BASE_WIDTH     500
#endif
#ifndef __WINDOW_BASE_HEIGHT
    #define __WINDOW_BASE_HEIGHT    500
#endif
#ifndef __WINDOW_PIXEL_DEPTH
    #define __WINDOW_PIXEL_DEPTH    32
#endif

#include <SFML/Graphics/RenderWindow.hpp>

#define __VIDEOMODE     sf::VideoMode(__WINDOW_BASE_WIDTH, \
                                       __WINDOW_BASE_HEIGHT,\
                                         __WINDOW_PIXEL_DEPTH)

#include "asset_manager.hpp"
#include "state_manager.hpp"

namespace Game {

static void load_textures(AssetManager &assets);;

inline const sf::VideoMode VideoMode    {__VIDEOMODE};
inline const sf::Vector2i  TileSize     {32, 32};

struct GameEngineData
{
    AssetManager assets;
    StateManager states;
    sf::RenderWindow window;
};

} // Game namespace

#endif // GAME_ENGINE_DATA_HPP