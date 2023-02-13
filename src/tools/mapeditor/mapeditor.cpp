#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "core/asset_manager.hpp"
#include "gui/tilesetWidget.hpp"

#include "graphics/map.hpp"

int main(int argc, char **argv)
{
    AssetManager assetMngr;
    assetMngr.loadTexture("tileset", "../resources/tilesetrpg.png");

    sf::RenderWindow window;
    sf::View windowView;
    window.create(sf::VideoMode(800, 800), "MapEditor");
    windowView.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    TilesetWidget tileset {assetMngr.getTexture("tileset"), sf::Vector2u(32,32), window};

    Map gameMap {sf::Vector2u(15,10), &tileset};

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            tileset.processEvents(event, window);
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                windowView.setSize(event.size.width, event.size.height);
                windowView.zoom(0.8);
                windowView.setCenter(gameMap.getGlobalBounds().getSize().x / 2,
                                     gameMap.getGlobalBounds().getSize().y / 2);
                window.setView(windowView);
                break;

            default:
                break;
            }

        }

        window.clear();


        tileset.update(window);

        window.draw(gameMap);
        window.draw(tileset);

        window.display();
    }

    return 0;
}
