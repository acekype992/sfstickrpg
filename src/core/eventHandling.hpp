#ifndef EVENT_HANDLING_HPP
#define EVENT_HANDLING_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

using Event = sf::Event;
using KeyEvent = sf::Event::KeyEvent;
using MouseMoveEvent = sf::Event::MouseMoveEvent;
using MouseButtonEvent = sf::Event::MouseButtonEvent;
using SizeEvent = sf::Event::SizeEvent;

class EventHandling
{
public:
    EventHandling() noexcept;
    virtual ~EventHandling() = default;

    void processEvents(const Event& event, sf::RenderWindow &window);
    void update(sf::RenderWindow &window);

    virtual sf::Time getUpdateTime() const noexcept = 0;

protected:
    virtual void keyPressEvent(const KeyEvent &event) {}
    virtual void keyReleaseEvent(const KeyEvent &event) {}
    virtual void mouseClickEvent(const MouseButtonEvent &event, sf::RenderWindow &window) {}
    virtual void mouseReleaseEvent(const MouseButtonEvent &event) {}
    virtual void mouseMoveEvent(const MouseMoveEvent &event, sf::RenderWindow &window) {}
    virtual void windowResizeEvent(const SizeEvent &event, sf::RenderWindow &window) {}

private:
    bool isKeyPressed_;
    std::unique_ptr<KeyEvent> currentKeyPressed_;

    bool isMouseButtonPressed_;
    std::unique_ptr<MouseButtonEvent> currentMouseButtonPressed_;

    sf::Clock clock_;
};

#endif // EVENT_HANDLING_HPP
