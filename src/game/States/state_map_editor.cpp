#include "state_map_editor.hpp"


void StateMapEditor::initialize()
{
    viewMapZoom_ = 1.f;
    tileset_ = &assets.getTileset("tileset");

    tilesetSprite_ = tileset_->getDrawableTileset();

    map_ = std::make_unique<Map>(*tileset_,
                                 60,
                                 60);


    recShape_.setSize(sf::Vector2f(32,32));
    recShape_.setFillColor(sf::Color(255, 0, 0, 100));

    tilShape_.setSize(sf::Vector2f(32,32));
    tilShape_.setFillColor(sf::Color(255, 0, 0, 100));
}

#include <iostream>
void StateMapEditor::pre_update()
{

}


void StateMapEditor::update()
{

}


void StateMapEditor::draw()
{
    window.setView(viewMap_);

    window.draw(*map_);

    window.setView(viewTileset_);



    auto vs = tilesetSprite_.getGlobalBounds();
//    std::cout << vs.getSize().x << ":" << vs.getSize().y << std::endl;
    sf::RectangleShape re {sf::Vector2f(vs.getSize())};
    re.setFillColor(sf::Color::Red);
    re.setPosition(sf::Vector2f(vs.getPosition()));
    window.draw(re);

    window.draw(tilesetSprite_);

//    if(drawTilShape_)
//        window.draw(tilShape_);

//    window.setView(viewMap_);
//    if(drawRecShape_)
//    {
//        window.draw(recShape_);
//    }
//    window.setView(viewTileset_);
}



void StateMapEditor::keyPressEvent(const Event::KeyEvent &event)
{
    auto windowSize = window.getSize();
    auto vp = viewMap_.getViewport().getPosition();
    switch(event.code)
    {
    case sf::Keyboard::Up:
        viewMap_.move(0, -32);
        break;
    case sf::Keyboard::Left:
        viewMap_.move(-32, 0);
        break;
    case sf::Keyboard::Right:
        viewMap_.move(32, 0);
        break;
    case sf::Keyboard::Down:
        viewMap_.move(0, 32);
        break;
    default:
        break;
    }
}


void StateMapEditor::keyReleaseEvent(const Event::KeyEvent &event)
{

}

#include <iostream>
void StateMapEditor::mouseMoveEvent(const Event::MouseMoveEvent &event)
{
    sf::Vector2i mousePos {window.mapPixelToCoords(sf::Vector2i(event.x, event.y))};
    sf::Vector2i mousePos2 {window.mapPixelToCoords(sf::Vector2i(event.x, event.y), viewTileset_)};

    if(tilesetSprite_.getGlobalBounds().contains(mousePos2.x, mousePos2.y))
    {
        auto p = mousePos2;
        p.x /= 32;
        p.y /= 32;

        tilShape_.setPosition(p.x * 32,
                              p.y * 32);
        drawTilShape_= true;
    }
    else
    {
        drawTilShape_ = false;
    }


    if(map_->getBoundingRect().contains(mousePos.x, mousePos.y))
    {
        for(const auto& rect : map_->tilesRect_)
        {
            if(rect.contains(mousePos.x, mousePos.y))
            {
                recShape_.setPosition(rect.getPosition().x, rect.getPosition().y);
                drawRecShape_ = true;
            }
        }

        if(mousePressed_ && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            map_->setTile(mousePos.x, mousePos.y, r);
        }
    }
    else
    {
        drawRecShape_ = false;
    }
}


void StateMapEditor::mouseClickEvent(const Event::MouseButtonEvent &event)
{
    if(drawTilShape_)
    {
        sf::Vector2i mousePos2 {window.mapPixelToCoords(sf::Vector2i(event.x, event.y), viewTileset_)};
        auto p = mousePos2;
        p.x /= 32;
        p.y /= 32;
        r = (*tileset_)(p.x, p.y);
    }
    mousePressed_ = true;
}


void StateMapEditor::mouseReleaseEvent(const MouseButtonEvent &event)
{
    mousePressed_ = false;
}


void StateMapEditor::resizeEvent(const Event::SizeEvent &event)
{
    auto vt = viewTileset_.getViewport();
    viewMap_.reset(sf::FloatRect(0, 0, event.width, event.height));
    viewMap_.setViewport(sf::FloatRect(0.5, 0.f, 1.0f, 1.0f));
//    viewMap_.zoom(viewMapZoom_);
//    window.setView(viewMap_);

//    viewTileset_.reset(sf::FloatRect(0, 0, event.width, event.height));
    viewTileset_.reset(sf::FloatRect(0,
                                     0,
                                     event.width,
                                     event.height));
    viewTileset_.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
//    tilesetSprite_.setScale(0.5, 0.5);

//    viewTileset_.reset(sf::FloatRect(0, 0, tilesetSprite_.getTexture()->getSize().x,
//                                           event.height));
//    viewTileset_.zoom(0.5f);
//    viewTileset_.setCenter(tilesetSprite_.getGlobalBounds().getSize().x / 2,
//                           tilesetSprite_.getGlobalBounds().getSize().y / 2);
//    tilesetSprite_.setScale(1, 1);
}
