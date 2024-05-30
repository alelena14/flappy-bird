#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#define WINDOWW 768 //x
#define WINDOWH 1024  //y

class Map {
private:
    sf::Sprite windowSprite1;
    sf::Sprite windowSprite2;
    sf::Sprite windowSprite3;
    sf::Texture windowText1;
    sf::Texture windowText2;
    float speedBackground;
public:
    Map(sf::Texture* bg_no_movement, sf::Texture* bg_movement);

    void bgScale(float scaleX1, float scaleY1, float scaleX2, float scaleY2);
    
    void bgPosition(sf::Vector2f position1, sf::Vector2f position2);

    void bgMove(float dt, float maxVelocity);

    sf::Sprite* getSprite1();

    sf::Sprite* getSprite2();

    sf::Sprite* getSprite3();
};

#endif // !MAP_H
