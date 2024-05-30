#include "Bird.h"

#define WINDOWW 1000 //x
#define WINDOWH 900  //y
#define BIRD_ANIMATION_TIMER 0.5f
#define PIPE_SPAWN_SPEED 10.f

Bird::Bird(sf::Vector2f scale) : scale{ scale } {
        shape.setScale(scale);
        currentVelocity = 0.f;
        state = 0;
        birdSpeed = 350.f;
        switchSpeed = 150.f;
        flyTime = 0.25f;
        shape.setPosition(WINDOWW / 4, WINDOWH / 2 - shape.getGlobalBounds().height);
        direction = sf::Vector2f(0.0f, -1.0f);
        rotationSpeedDown = 100.f;
        rotationSpeedUp = 500.f;
        rotation = 0;
        switchTime = 0;

        sf::Texture text1;
        text1.loadFromFile("Textures/flappy1.png");
        animationSprites.push_back(text1);
        sf::Texture text2;
        text2.loadFromFile("Textures/flappy2.png");
        animationSprites.push_back(text2);
        sf::Texture text3;
        text3.loadFromFile("Textures/flappy3.png");
        animationSprites.push_back(text3);
        sf::Texture text4;
        text4.loadFromFile("Textures/flappy2.png");
        animationSprites.push_back(text4);
        sf::Vector2f origin(text1.getSize().x / 2, text1.getSize().y / 2);

        shape.setOrigin(origin);
        shape.setTexture(animationSprites[animationIt]);
    }

    void Bird::animate() {
        if (animationClock.getElapsedTime().asSeconds() > BIRD_ANIMATION_TIMER / animationSprites.size())
        {
            if (animationIt < animationSprites.size() - 1)
                animationIt++;
            else
                animationIt = 0;
            shape.setTexture(animationSprites[animationIt]);
            animationClock.restart();
        }
    }

    sf::Sprite* Bird::getShape() { return &shape; }

    void Bird::initFly(float dt) {
        switchTime++;
        if (switchTime >= 20) {
            direction.y = direction.y* (-1);
            switchTime = 0;
        }
        shape.move(0, switchSpeed*direction.y * dt);
    }

    void Bird::fly(float dt) {
        
        if (state == 1) {    //fly
            shape.move(0, -birdSpeed * dt);
            rotation -= dt * rotationSpeedUp;
            if (rotation < -25.f)
                rotation = -25.f;
            
            shape.setRotation(rotation);
        }
        else if (state == 2) {  //fall
            shape.move(0, birdSpeed * dt);
            rotation += dt * rotationSpeedDown;
            if (rotation > 87.f)
                rotation = 87.f;
            shape.setRotation(rotation);
        }
        if (flyClock.getElapsedTime().asSeconds() > flyTime){
            flyClock.restart();
            state = 2;
        }
            
    }

    void Bird::tap() {
        flyClock.restart();
        state = 1;
    }

    void Bird::fall(float dt) {
        shape.move(0, birdSpeed * dt);
        rotation += dt * rotationSpeedDown;
        if (rotation > 87.f)
            rotation = 87.f;
        shape.setRotation(rotation);
    }