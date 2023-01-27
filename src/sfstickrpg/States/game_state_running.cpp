#include "game_state_running.hpp"


void GameStateRunning::loadMaps()
{
    Map map {assets.getTileset("tileset"), "../resources/maps/map0"};
    mapByString_.insert({"map1", std::move(map)});

    currentMap_ = &mapByString_.find("map1")->second;
}


void GameStateRunning::initialize()
{
    loadMaps();

    keyPressed_ = false;

    gameViewZoom_ = 0.5f;



    player_.initialize(assets.getTileset("player"));
    player_.speed = 2.f;
    player_.setAnim(4);
    player_.setMapPosition(5, 5);
}


void GameStateRunning::pre_update()
{
    movePlayer();

    player_.update();
}


void GameStateRunning::update()
{
    window.setView(gameView_);
    gameView_.setCenter(player_.getPosition());
}


void GameStateRunning::draw()
{
    window.draw(*currentMap_);
    window.draw(player_);
}


void GameStateRunning::movePlayer()
{
    if(keyPressed_ && lastKeyPressed_.get())
    {
        if(lastKeyPressed_->code == sf::Keyboard::Up)
        {
            player_.direction = Entity::Direction::up;
            if(player_.getPosition().y > 0)
            {
                player_.move(0, -player_.speed);
            }
            player_.animOn = true;
        }
        else if(lastKeyPressed_->code == sf::Keyboard::Left)
        {
            player_.direction = Entity::Direction::left;
            if(player_.getPosition().x > 0)
            {
                player_.move(-player_.speed, 0);
            }
            player_.animOn = true;
        }
        else if(lastKeyPressed_->code == sf::Keyboard::Right)
        {
            player_.direction = Entity::Direction::right;
            if(player_.getPosition().x < currentMap_->getSize().x)
            {
                player_.move(player_.speed, 0);
            }
            player_.animOn = true;
        }
        else if(lastKeyPressed_->code == sf::Keyboard::Down)
        {
            player_.direction = Entity::Direction::down;
            if(player_.getPosition().y < currentMap_->getSize().y)
            {
                player_.move(0, player_.speed);
            }
            player_.animOn = true;

        }
    }
    else
    {
        player_.animOn = false;
    }
}


void GameStateRunning::keyPressEvent(const Event::KeyEvent &event)
{
    keyPressed_ = true;
    lastKeyPressed_ = std::make_unique<sf::Event::KeyEvent>(event);
}


void GameStateRunning::keyReleaseEvent(const Event::KeyEvent &event)
{
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
    && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
    && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
    && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
    ){
        keyPressed_ = false;
    }
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
