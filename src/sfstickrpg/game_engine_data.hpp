#ifndef GAME_ENGINE_DATA_HPP
#define GAME_ENGINE_DATA_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "asset_manager.hpp"
#include "state_manager.hpp"

using Window = sf::RenderWindow;
using VideoMode = sf::VideoMode;

struct GameEngineData
{
    AssetManager assets;
    StateManager states;
    Window window;
};

#endif // GAME_ENGINE_DATA_HPP
