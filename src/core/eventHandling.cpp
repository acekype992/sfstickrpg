#include "eventHandling.hpp"


EventHandling::EventHandling() noexcept
    : isKeyPressed_ {false}, isMouseButtonPressed_ {false}
{
}


void EventHandling::processEvents(const Event &event, sf::RenderWindow &window)
{
    switch(event.type)
    {
    case Event::KeyPressed:
        if(!currentKeyPressed_ || currentKeyPressed_->code != event.key.code)
        {
            keyPressEvent(event.key);
            clock_.restart();
        }
        isKeyPressed_ = true;
        currentKeyPressed_ = std::make_unique<KeyEvent>(event.key);
        break;
    case Event::KeyReleased:
        if(currentKeyPressed_ && currentKeyPressed_->code == event.key.code)
        {
            isKeyPressed_ = false;
            currentKeyPressed_.reset();
        }
        keyReleaseEvent(event.key);
        break;
    case Event::MouseButtonPressed:
        isMouseButtonPressed_ = true;
        currentMouseButtonPressed_ = std::make_unique<MouseButtonEvent>(event.mouseButton);
        break;
    case Event::MouseButtonReleased:
        isMouseButtonPressed_ = false;
        currentMouseButtonPressed_.reset();
        mouseReleaseEvent(event.mouseButton);
        break;
    case Event::MouseMoved:
        mouseMoveEvent(event.mouseMove, window);
        break;
    case Event::Resized:
        windowResizeEvent(event.size, window);
        break;

    default:
        break;
    }

}


void EventHandling::update(sf::RenderWindow &window)
{
    if(clock_.getElapsedTime() > getUpdateTime())
    {
        if(isKeyPressed_ && currentKeyPressed_)
            keyPressEvent(*currentKeyPressed_.get());

        clock_.restart();
    }

    if(isMouseButtonPressed_ && currentMouseButtonPressed_)
        mouseClickEvent(*currentMouseButtonPressed_.get(), window);
}
