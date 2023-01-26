#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "tileset.hpp"


class Map : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    using matrix_t  = ack::Matrix<int>;
    using size_type = unsigned int;

public:
    Map(const std::string &filename, const Tileset &tileset);
    Map(Map &&map)
        : tileset_ {std::move(map.tileset_)}
        , vertices_ {std::move(map.vertices_)}
    {}

    const Tileset& getTileset() const noexcept;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const Tileset &tileset_;
    sf::VertexArray vertices_;
};


#endif // MAP_HPP
