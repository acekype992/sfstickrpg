#include "game_state_running.hpp"
#include <SFML/Graphics.hpp>

void GameStateRunning::loadMaps()
{
    Map map {assets.getTileset("tileset"), "../resources/maps/map1"};
    mapByString_.insert({"map1", std::move(map)});

    currentMap_ = &mapByString_.find("map1")->second;
}


void GameStateRunning::initialize()
{
    loadMaps();

    keyPressed_ = false;

    gameViewZoom_ = 0.45f;



    player_.initialize(assets.getTileset("player"));
    player_.speed = 2.f;
    player_.setAnim(4);
    player_.setMapPosition(5, 0);
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

//    sf::FloatRect mapBounding = currentMap_->getBoundingRect();
//    sf::RectangleShape r{sf::Vector2f(mapBounding.getSize())};
//    r.setOutlineColor(sf::Color::Red);
//    r.setOutlineThickness(1);
//    r.setFillColor(sf::Color::Transparent);

//    sf::FloatRect playerBounding = player_.getBoundingRect();
//    sf::RectangleShape rr {sf::Vector2f(playerBounding.getSize())};
//    rr.setOutlineColor(sf::Color::Red);
//    rr.setOutlineThickness(1);
//    rr.setFillColor(sf::Color::Transparent);
//    rr.setPosition(player_.getPosition());

//    window.draw(r);
//    window.draw(rr);
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
            if(player_.getPosition().x < (currentMap_->getSize().x - GameEngine::TileSize.y))
            {
                player_.move(player_.speed, 0);
            }
            player_.animOn = true;
        }
        else if(lastKeyPressed_->code == sf::Keyboard::Down)
        {
            player_.direction = Entity::Direction::down;
            if(player_.getPosition().y < (currentMap_->getSize().y - GameEngine::TileSize.y))
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
