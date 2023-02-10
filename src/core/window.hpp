#ifndef WINDOW_HPP
#define  WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>


class Window
{
    using size_type = unsigned int;

public:
    Window();
    Window(size_type width, size_type height);

    virtual ~Window() = default;

private:
    sf::RenderWindow window_;
};


#endif // WINDOW_HPP
