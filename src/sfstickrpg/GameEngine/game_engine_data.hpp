#ifndef GAME_ENGINE_DATA_HPP
#define GAME_ENGINE_DATA_HPP

#define __WINDOW_BASE_WIDTH     800
#define __WINDOW_BASE_HEIGHT    800
#define __WINDOW_PIXEL_DEPTH    32

#include <SFML/Graphics/RenderWindow.hpp>

#define __VIDEOMODE     sf::VideoMode(__WINDOW_BASE_WIDTH, \
                                       __WINDOW_BASE_HEIGHT,\
                                         __WINDOW_PIXEL_DEPTH)

#include "asset_manager.hpp"
#include "state_manager.hpp"

namespace GameEngine {

static void load_textures(AssetManager &assets)
{

}

inline const sf::VideoMode VideoMode    {__VIDEOMODE};
inline const sf::Vector2i  TileSize     {32, 32};

struct GameEngineData
{
    AssetManager assets;
    StateManager states;
    sf::RenderWindow window;
};

} // GameEngine namespace

#endif // GAME_ENGINE_DATA_HPP
