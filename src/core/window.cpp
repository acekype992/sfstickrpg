#include "window.hpp"

#include <SFML/Window/Event.hpp>

Window::Window(size_type width, size_type height, const std::string &title)
{
    window_.create(sf::VideoMode(width, height), title);
    windowView_.reset(sf::FloatRect(0, 0, width, height));
}


void Window::show()
{
    while(window_.isOpen())
    {
        processEvents();
    }
}


void Window::processEvents()
{
    sf::Event event;
    while(window_.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;

        default:
            break;
        }
    }
}
