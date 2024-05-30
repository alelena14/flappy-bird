#ifndef BIRD_H
#define BIRD_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Bird {
private:

    sf::Sprite shape;
    std::vector<sf::Texture> animationSprites;
    unsigned int animationIt = 0;
    sf::Clock animationClock;
    sf::Vector2f scale;
    float currentVelocity;
    int state;
    float birdSpeed;
    float switchSpeed;
    sf::Clock flyClock;
    float flyTime;
    sf::Vector2f direction;
    float rotation;
    float rotationSpeedDown;
    float rotationSpeedUp;
    int switchTime;

public:

    Bird(sf::Vector2f scale);

    void animate();

    sf::Sprite* getShape();

    void initFly(float dt);

    void fly(float dt);

    void tap();

    void fall(float dt);
};

#endif