#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player {
    private:
        sf::Texture texture;
        sf::Vector2f position;
        float speed;

    public:
        sf::Sprite sprite;
        sf::Event event;
        sf::RenderWindow window;

        Player(const sf::Texture &texture, sf::IntRect initialRect, sf::Vector2f position, sf::Event event);

        // update position of player
        void updatePosition(sf::Vector2f position);

        // implement movement logic based on user input
        void move(sf::Vector2f direction);
};

#endif