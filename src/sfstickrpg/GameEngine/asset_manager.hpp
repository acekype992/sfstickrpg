#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <unordered_map>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

using Font = sf::Font;
using Texture = sf::Texture;

class AssetManager
{
public:
    AssetManager() noexcept = default;
    ~AssetManager() noexcept = default;

    void loadTexture(const std::string &name, const std::string &filename);
    Texture& getTexture(const std::string &name);

    void loadFont(const std::string &name, const std::string &filename);
    Font& getFont(const std::string &name);

private:
    std::unordered_map<std::string, Texture> textures_;
    std::unordered_map<std::string, Font> fonts_;
};

#endif // ASSET_MANAGER_HPP
