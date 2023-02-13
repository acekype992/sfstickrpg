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

#include "core/inputEventHandler.hpp"


class Tileset : public sf::Drawable, sf::Transformable
{
    using size_type = unsigned int;


    class EventHandle : public InputEventHandler
    {
    public:
        EventHandle(Tileset &tileset) noexcept : tileset_ {tileset}
        {}

        virtual void keyPressEvent(const KeyEvent &event) override
        {
            if(event.code == sf::Keyboard::T)
            {
                bool &drawEnable = tileset_.drawEnable_;
                drawEnable ? drawEnable = false : drawEnable = true;
            }
        }


        virtual void keyReleaseEvent(const KeyEvent &event) override
        {

        }


        virtual void mouseClickEvent(const MouseButtonEvent &event, sf::RenderWindow &window) override
        {
            if(tileset_.drawEnable_ && tileset_.drawCurrentCase_)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.x, event.y));
                int px = mousePos.x / 32;
                int py = mousePos.y / 32;

                const auto &r = tileset_(px, py);
                tileset_.selectCase_.setPosition(r.left * 32, r.top * 32);
            }
        }


        virtual void mouseReleaseEvent(const MouseButtonEvent &event) override
        {

        }


        virtual void mouseMoveEvent(const MouseMoveEvent &event, sf::RenderWindow &window) override
        {
            if(tileset_.drawEnable_)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.x, event.y));
                int px = mousePos.x;
                int py = mousePos.y;

                if(tileset_.getGlobalBounds().contains(px, py))
                {
                    px /= 32;
                    py /= 32;

                    const auto &r = tileset_(px, py);
                    tileset_.currentCase_.setPosition(r.left * 32, r.top * 32);
                    tileset_.drawCurrentCase_ = true;
                }
                else
                {
                    tileset_.drawCurrentCase_ = false;
                }

            }
        }

    private:
        Tileset &tileset_;
    };

    friend class EventHandle;


public:
    EventHandle eventHandle_;
    Tileset(sf::Vector2u tileSize, const std::string &filename);

    Tileset(const Tileset&) = delete;
    Tileset& operator=(const Tileset&) = delete;

    virtual ~Tileset() noexcept = default;

    sf::Vector2u sizeOfTileset() const noexcept;
    sf::Vector2u sizeOfTiles() const noexcept;

    sf::IntRect operator()(size_type x, size_type y) const noexcept;
    sf::IntRect operator[](size_type i) const noexcept;

    sf::Texture& getTexture() const noexcept;
    sf::IntRect getGlobalBounds() const noexcept;


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
