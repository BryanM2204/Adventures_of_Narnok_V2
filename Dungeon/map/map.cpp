#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "map.h"
#include <unordered_map>

// Create a map to associate tile numbers with their corresponding texture bounds
std::unordered_map<float, TextureBounds> tileTextureMap = {
    {1, {32, 48, 16, 16}}, // Floor tile
    {2, {272, 12, 16, 16}}, // Horizontal North Wall
    {3, {309, 44, 16, 16}},// Horizontal South Wall
    {4, {331, 16, 16, 16}},// Vertical East Wall
    {5, {293, 16, 16, 16}},// Vertical West Wall
    {6, {293, 0, 16, 16}}, // Top Left Corner
    {7, {331, 0, 16, 16}}, // Top Right Corner
    {8, {293, 44, 16, 16}},// Bottom Left Corner
    {9, {331, 44, 16, 16}} // Bottom Right Corner
};


bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<int>>& dungeonGrid) {
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // Resize the vertex array based on dungeon dimensions
    unsigned int width = dungeonGrid[0].size();
    unsigned int height = dungeonGrid.size();

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = dungeonGrid[j][i];

            if (tileNumber == 0)
                continue;

            // Find the bounds for this tile in the tileset
            if (tileTextureMap.find(tileNumber) == tileTextureMap.end())
                continue; // Skip if tileNumber is not in the map

            const TextureBounds& bounds = tileTextureMap[tileNumber];

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = sf::Vector2f(bounds.x, bounds.y);
            triangles[1].texCoords = sf::Vector2f(bounds.x + bounds.w, bounds.y);
            triangles[2].texCoords = sf::Vector2f(bounds.x, bounds.y + bounds.h);
            triangles[3].texCoords = sf::Vector2f(bounds.x, bounds.y + bounds.h);
            triangles[4].texCoords = sf::Vector2f(bounds.x + bounds.w, bounds.y);
            triangles[5].texCoords = sf::Vector2f(bounds.x + bounds.w, bounds.y + bounds.h);
        }

    m_tileSize = tileSize;

    return true;
}



void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}

sf::Vector2u m_tileSize; // Declare m_tileSize member variable
