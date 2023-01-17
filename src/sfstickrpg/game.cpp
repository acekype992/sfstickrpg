#include "game_engine_data.hpp"
#include "game_state_running.hpp"

#define WINDOW_BASE_WIDTH   1200
#define WINDOW_BASE_HEIGHT  1000

namespace Game {
void load_textures(AssetManager &assets);
}


int main(int argc, char **argv)
{
    constexpr const std::string_view window_title {"SF Stick RPG"};
    constexpr unsigned int window_base_width    {WINDOW_BASE_WIDTH};
    constexpr unsigned int window_base_height   {WINDOW_BASE_HEIGHT};

    std::shared_ptr<GameEngineData> geData;
    geData = std::make_shared<GameEngineData>();

    const VideoMode vm {window_base_width, window_base_height};
    geData->window.create(vm, window_title.data());

    Game::load_textures(geData->assets);

    geData->states.addState(std::make_unique<GameStateRunning>(geData));
    while(geData->window.isOpen())
    {
        geData->states.process();

        geData->states.currentState()->processEvent();

        geData->states.currentState()->update(0);

        geData->window.clear();
        geData->states.currentState()->draw();
        geData->window.display();
    }

    return 0;
}


void Game::load_textures(AssetManager &assets)
{

}
