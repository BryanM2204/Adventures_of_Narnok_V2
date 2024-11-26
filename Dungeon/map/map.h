#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#ifndef MAP_H
#define MAP_H

// Define a struct to hold texture bounds
struct TextureBounds {
    float x, y, w, h;
};

class TileMap : public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u m_tileSize;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<int>>& dungeonGrid);
    sf::Vector2u getTileSize() const {
        return m_tileSize;
    }
};

#endif