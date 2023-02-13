#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <memory>
#include <unordered_map>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>


class AssetManager
{
    using TexturePtr = std::unique_ptr<sf::Texture>;
    using FontPtr    = std::unique_ptr<sf::Font>;

public:
    AssetManager() noexcept = default;
    ~AssetManager() noexcept = default;

    void loadTexture(const std::string &name, const std::string &filename, bool smoothOn = false, bool repeatOn = false);
    sf::Texture& getTexture(const std::string &name);

    void loadFont(const std::string &name, const std::string &filename, bool smoothOn = false);
    sf::Font& getFont(const std::string &name);

private:
    std::unordered_map<std::string, TexturePtr> textures_;
    std::unordered_map<std::string, FontPtr> fonts_;
};

#endif // ASSET_MANAGER_HPP
