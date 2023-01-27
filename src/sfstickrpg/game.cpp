#define __WINDOW_BASE_WIDTH     800
#define __WINDOW_BASE_HEIGHT    800
#define __WINDOW_PIXEL_DEPTH    32

#include "Core/game_engine_data.hpp"
#include "States/game_state_running.hpp"


int main(int argc, char **argv)
{
    constexpr const std::string_view window_title {"SF Stick RPG"};

    GameEngine::GameEngineData geData;
    GameEngine::load_textures(geData.assets);

    geData.window.create(GameEngine::VideoMode, window_title.data(), sf::Style::Default);
    geData.window.setVerticalSyncEnabled(true);
    geData.window.setKeyRepeatEnabled(false);

    geData.states.add_state(std::make_unique<GameStateRunning>(geData));

    while(geData.window.isOpen())
    {
        geData.states.process();

        geData.states.current_state()->process_event();
        geData.states.current_state()->pre_update();
        geData.states.current_state()->update();

        geData.window.clear(sf::Color::Black);
        geData.states.current_state()->draw();
        geData.window.display();
    }

    return 0;
}


static void GameEngine::load_textures(AssetManager &assets)
{
    assets.loadTileset("tileset", sf::Vector2u(32,32) , "../resources/tilesetrpg.png");
    assets.loadTileset("player", sf::Vector2u(32,32), "../resources/player.png");
}
