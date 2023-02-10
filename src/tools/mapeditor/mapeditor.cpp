#include "graphics/tileset.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>


int main(int argc, char **argv)
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 800), "MapEditor");

    sf::View view;
//    Tileset tileset {sf::Vector2u(32,32), "../resources/mytileset.png"};
    Tileset tileset {sf::Vector2u(32,32), "../resources/tilesetrpg.png"};

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                view.setSize(event.size.width, event.size.height);
                view.zoom(0.8);
                view.setCenter(tileset.getGlobalBounds().getPosition().x + (tileset.getGlobalBounds().getSize().x / 2),
                               tileset.getGlobalBounds().getPosition().y + (tileset.getGlobalBounds().getSize().y / 2));
                window.setView(view);
                break;
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
                tileset.keyPressEvent(event.key);
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
                tileset.mouseClickEvent(event.mouseButton, window);
                break;
            case sf::Event::MouseMoved:
                tileset.mouseMoveEvent(event.mouseMove, window);
                break;

            default:
                break;
            }
        }

        window.clear();

        window.draw(tileset);

        window.display();
    }

    return 0;
}
