#include <SFML/Graphics.hpp>
#include "Player/player.h"
#include "Dungeon/map/map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Adventures of Narnok");

    window.setVerticalSyncEnabled(true);

    bool fullscreen = false;

    sf::Texture texture;


    if(!texture.loadFromFile("./Assets/Sprites/Narnok.png")){
        return 1;
    }

    // define the level with an array of tile indices
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    // create the tile map from the level definition
    TileMap map;
    if (!map.load("./Assets/Sprites/TEST.png", sf::Vector2u(32, 32), level, 16, 8))
        return -1;

    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    view.zoom(0.65f);
    window.setView(view);
    map.setScale(2, 2);

    sf::IntRect rightFace(0, 0, 32, 32);
    sf::IntRect leftFace(32, 0, 32, 32);
    sf::IntRect downFace(32, 32, 32, 32);
    sf::IntRect upFace(0, 32, 32, 32);
    
    Player Player(texture, downFace, sf::Vector2f(400, 300), sf::Event());

    // Resize the player sprite
    Player.sprite.setScale(2, 2);

    sf::Clock timer;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F11) {
                    // switch boolean to true
                    fullscreen = !fullscreen;
                    if (fullscreen){
                        window.create(sf::VideoMode::getDesktopMode(), "Adventures of Narnok", sf::Style::Fullscreen);
                    }
                    else {
                        window.create(sf::VideoMode(800, 600), "Adventures of Narnok", sf::Style::Default);
                    }
                    view.setSize(window.getSize().x, window.getSize().y);
                    view.setCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
                    view.zoom(0.65f);
                    window.setView(view);

                }
            }
        }

        window.clear();

        sf::Vector2f direction = {0.f, 0.f};

        sf::Time passed = timer.restart();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            Player.sprite.setTextureRect(upFace);
            direction.y -= 4 * map.getTileSize().y * passed.asSeconds();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            Player.sprite.setTextureRect(downFace);
            direction.y += 4 * map.getTileSize().y * passed.asSeconds();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            Player.sprite.setTextureRect(leftFace);
            direction.x -= 4 * map.getTileSize().x * passed.asSeconds();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            Player.sprite.setTextureRect(rightFace);
            direction.x += 4 * map.getTileSize().x * passed.asSeconds();
        }

        Player.move(direction);

        sf::Vector2f viewCenter(Player.sprite.getPosition().x + Player.sprite.getGlobalBounds().width / 2, Player.sprite.getPosition().y + Player.sprite.getGlobalBounds().height / 2);
        view.setCenter(viewCenter);
        window.setView(view);

        

        window.draw(map);
        window.draw(Player.sprite);

        window.display();
    }

    return 0;
}