#include <cassert>
#include "asset_manager.hpp"

void AssetManager::loadTexture(const std::string &name, const std::string &filename)
{
    assert(textures_.find(name) == textures_.end() &&
           "the name to identify the texture already exists");

    sf::Texture texture;
    if(texture.loadFromFile(filename))
    {
        textures_.insert({name, texture});
    }
}

Texture& AssetManager::getTexture(const std::string &name)
{
    assert(textures_.find(name) != textures_.end() &&
            "the requested texture cannot be found");

    return textures_[name];
}

void AssetManager::loadFont(const std::string &name, const std::string &filename)
{
    assert(textures_.find(name) == textures_.end() &&
           "the name to identify the font already exists");

    sf::Font font;
    if(font.loadFromFile(filename))
    {
        fonts_.insert({name, font});
    }
}

Font& AssetManager::getFont(const std::string &name)
{
    assert(fonts_.find(name) != fonts_.end() &&
            "the requested font cannot be found");

    return fonts_[name];
}
