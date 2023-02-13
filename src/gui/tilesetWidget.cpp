#include "tilesetWidget.hpp"


TilesetWidget::TilesetWidget(sf::Texture& texture, const sf::Vector2u &tileSize, sf::RenderWindow &window)
    : Tileset {texture, tileSize}
    , isVisible_ {true}
{
    tileHovered_.setSize(sf::Vector2f(getTileSize()));
    tileHovered_.setFillColor(sf::Color(255, 255, 255, 120));

    focusedTile_.setSize(sf::Vector2f(getTileSize()));
    focusedTile_.setFillColor(sf::Color(155, 155, 155, 180));

    boundingRect_.setSize(sf::Vector2f(getGlobalBounds().getSize()));
    boundingRect_.setPosition(getGlobalBounds().getPosition().x,
                              getGlobalBounds().getPosition().y);
    boundingRect_.setFillColor(sf::Color::Transparent);
    boundingRect_.setOutlineColor(sf::Color::Red);
    boundingRect_.setOutlineThickness(1);

    view_.reset(sf::FloatRect(0,
                              0,
                              window.getView().getSize().x,
                              window.getView().getSize().y));
}


sf::Time TilesetWidget::getUpdateTime() const noexcept
{
    return sf::seconds(0.3f);
}


void TilesetWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(isVisible_)
    {
        const sf::View windowView {target.getView()};
        target.setView(view_);

        states.transform *= getTransform();
        states.texture = &getTexture();

        target.draw(vertices(), states);
        target.draw(boundingRect_, states);
        target.draw(focusedTile_, states);
        if(isTileHoverVisible_)
        {
            target.draw(tileHovered_, states);
        }

        target.setView(windowView);
    }
}


void TilesetWidget::keyPressEvent(const KeyEvent &event)
{
    if(event.code == sf::Keyboard::T)
    {
        isVisible_ ? isVisible_ = false : isVisible_ = true;
    }
}


void TilesetWidget::keyReleaseEvent(const KeyEvent &event)
{

}


void TilesetWidget::mouseClickEvent(const MouseButtonEvent &event, sf::RenderWindow &window)
{
    if(isVisible_ && isTileHoverVisible_)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.x, event.y), view_);
        int px = mousePos.x / 32;
        int py = mousePos.y / 32;

        const auto &r = tiles(px, py);
        focusedTile_.setPosition(r.left * 32, r.top * 32);
    }
}


void TilesetWidget::mouseReleaseEvent(const MouseButtonEvent &event)
{

}


void TilesetWidget::mouseMoveEvent(const MouseMoveEvent &event, sf::RenderWindow &window)
{
    if(isVisible_)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.x, event.y), view_);
        int px = mousePos.x;
        int py = mousePos.y;

        if(getGlobalBounds().contains(px, py))
        {
            px /= 32;
            py /= 32;

            const auto &r = tiles(px, py);
            tileHovered_.setPosition(r.left * 32, r.top * 32);
            isTileHoverVisible_ = true;
        }
        else
        {
            isTileHoverVisible_ = false;
        }

    }
}


void TilesetWidget::windowResizeEvent(const SizeEvent &event, sf::RenderWindow &window)
{
    view_.reset(sf::FloatRect(0,
                              0,
                              event.width,
                              event.height));

    view_.setCenter(getGlobalBounds().getPosition().x + (getGlobalBounds().getSize().x / 2),
                    getGlobalBounds().getPosition().y + (getGlobalBounds().getSize().y / 2));
}
