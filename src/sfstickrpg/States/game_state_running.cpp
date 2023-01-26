#include "game_state_running.hpp"

void GameStateRunning::initialize()
{
    gameViewZoom_ = 0.55f;

    Tileset& tileset = assets.getTileset("tileset");
    mapByString_.insert({"map1", std::move(Map("../resources/Maps/mat1", tileset))});

    currentMap_ = &mapByString_.find("map1")->second;
}


void GameStateRunning::pre_update()
{
    gameView_.setCenter(5 * 32,
                        5 * 32);
}


void GameStateRunning::update()
{
    window.setView(gameView_);
}


void GameStateRunning::draw()
{
    window.draw(*currentMap_);
}


void GameStateRunning::keyPressEvent(const Event::KeyEvent &event)
{

}


void GameStateRunning::keyReleaseEvent(const Event::KeyEvent &event)
{

}


void GameStateRunning::mouseMoveEvent(const Event::MouseMoveEvent &event)
{
}


void GameStateRunning::mouseClickEvent(const Event::MouseButtonEvent &event)
{

}


void GameStateRunning::resizeEvent(const Event::SizeEvent &event)
{
    gameView_.reset(sf::FloatRect(0, 0, event.width, event.height));
    gameView_.zoom(gameViewZoom_);
}
