#include <cassert>
#include "asset_manager.hpp"

void AssetManager::loadTexture(const std::string &name, const std::string &filename, bool smoothOn, bool repeatOn)
{
    assert(textures_.find(name) == textures_.end() &&
           "the name to identify the texture already exists");

    TexturePtr texture = std::make_unique<sf::Texture>();
    if(texture->loadFromFile(filename))
    {
        texture->setSmooth(smoothOn);
        texture->setRepeated(repeatOn);
        textures_.insert({name, std::move(texture)});
    }
}

sf::Texture& AssetManager::getTexture(const std::string &name)
{
    assert(textures_.find(name) != textures_.end() &&
            "the requested texture cannot be found");

    return *textures_[name].get();
}


void AssetManager::loadTileset(const std::string &name, const std::string &filename, bool smoothOn, bool repeatOn)
{
    assert(tilesets_.find(name) == tilesets_.end() &&
           "the name to identify the tileset already exists");

    sf::Texture texture;
    if(!texture.loadFromFile(filename))
        throw std::runtime_error("Cannot open file for load tileset");

    texture.setSmooth(smoothOn);
    texture.setRepeated(repeatOn);

    TilesetPtr tileset = std::make_unique<Tileset>(32, 32, texture);
    tilesets_.insert({name, std::move(tileset)});
}

Tileset& AssetManager::getTileset(const std::string &name)
{
    assert(tilesets_.find(name) != tilesets_.end() &&
            "the requested tileset cannot be found");

    return *tilesets_[name].get();
}


void AssetManager::loadFont(const std::string &name, const std::string &filename, bool smoothOn)
{
    assert(fonts_.find(name) == fonts_.end() &&
           "the name to identify the font already exists");

    FontPtr font = std::make_unique<sf::Font>();
    if(font->loadFromFile(filename))
    {
        font->setSmooth(smoothOn);
        fonts_.insert({name, std::move(font)});
    }
}

sf::Font& AssetManager::getFont(const std::string &name)
{
    assert(fonts_.find(name) != fonts_.end() &&
            "the requested font cannot be found");

    return *fonts_[name].get();
}
