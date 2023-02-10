#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <unordered_map>

#include "SFML/Graphics/RenderWindow.hpp"
#include "ackmatrix/matrix.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

class Tileset : public sf::Drawable, sf::Transformable
{
    using size_type = unsigned int;

public:
    Tileset(sf::Vector2u tileSize, const std::string &filename);
    Tileset(const Tileset&) = delete;
    Tileset& operator=(const Tileset&) = delete;

    ~Tileset() noexcept = default;

    sf::Vector2u sizeOfTileset() const noexcept;
    sf::Vector2u sizeOfTiles() const noexcept;

    sf::IntRect operator()(size_type x, size_type y) const noexcept;
    sf::IntRect operator[](size_type i) const noexcept;

    sf::Texture& getTexture() const noexcept;
    sf::IntRect getGlobalBounds() const noexcept;

    void keyPressEvent(const sf::Event::KeyEvent &event);
    void mouseClickEvent(const sf::Event::MouseButtonEvent &event, const sf::RenderWindow &window);
    void mouseMoveEvent(sf::Event::MouseMoveEvent &event, const sf::RenderWindow &window);
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    bool drawEnable_;
    std::unique_ptr<sf::Texture> texture_;
    sf::Vector2u tilesetSize_;
    sf::Vector2u tileSize_;

    sf::VertexArray vertices_;
    std::unordered_map<std::size_t, sf::IntRect> tiles_;
    ack::Matrix<sf::IntRect> tilesMatrix_;

    bool keyControlPressed();
    bool keyMajPressed();


    bool drawCurrentCase_;
    sf::RectangleShape currentCase_;
    sf::RectangleShape selectCase_;
};

#endif // TILESET_HPP
