#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "tileset.hpp"


class Map : public sf::Drawable, public sf::Transformable
{
    using size_type = unsigned int;

public:
    Map(const Tileset &tileset, const std::string &filename);

    ~Map() noexcept = default;

    sf::Vector2u getSize() const noexcept;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const Tileset &tileset_;
    sf::VertexArray vertices_;

    ack::Matrix<int> mapMatrix_;
};

#endif // MAP_HPP
