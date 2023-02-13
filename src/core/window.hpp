#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "notcopyable.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

class Window : public NotCopyable
{
    using size_type = unsigned int;

public:
    Window(size_type width, size_type height, const std::string &title);
    ~Window() noexcept = default;

    void show();

private:
    void processEvents();

    sf::RenderWindow window_;
    sf::View windowView_;

};


#endif // WINDOW_HPP
