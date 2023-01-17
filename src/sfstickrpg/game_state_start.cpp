#include <SFML/Graphics.hpp>
#include "game_state_start.hpp"


void GameStateStart::initialize()
{
    background_.setTexture(assets().getTexture("bg-start-menu"));
}


void GameStateStart::draw()
{
    window().setView(view_);

    window().draw(background_);
}


void GameStateStart::update(float dt)
{
}


void GameStateStart::pause()
{

}


void GameStateStart::resume()
{

}


void GameStateStart::keyPressEvent(const Event::KeyEvent &event)
{

}


void GameStateStart::keyReleaseEvent(const Event::KeyEvent &event)
{

}


void GameStateStart::mouseMoveEvent(const Event::MouseMoveEvent &event)
{

}


void GameStateStart::mouseClickEvent(const Event::MouseButtonEvent &event)
{

}


void GameStateStart::resizeEvent(const Event::SizeEvent &event)
{
    view_.setSize(event.width, event.height);
    background_.setPosition(window().mapPixelToCoords(sf::Vector2i(0, 0), view_));
    sf::Vector2i backgroundSize {background_.getTexture()->getSize()};
    background_.setScale(float(event.width) / float(backgroundSize.x),
                         float(event.height) / float(backgroundSize.y));
}

