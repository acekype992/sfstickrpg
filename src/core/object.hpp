#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <array>

class Object
{
    static constexpr inline std::size_t MAX_COMPONENTS {0xF};

public:
    enum class ComponentType {
        Drawable,
    };

private:
    std::array<bool, MAX_COMPONENTS> components_;
};

#endif // OBJECT_HPP
