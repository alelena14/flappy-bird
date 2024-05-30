#include <stdlib.h>
#include "Bird.h"
#include "Pipe.h"
#include "Map.h"


int main() {
    std::srand(NULL);
    sf::RenderWindow window(sf::VideoMode(WINDOWW, WINDOWH), "Flappy Bird");
    window.setFramerateLimit(60);

    Bird bird(sf::Vector2f(5.f, 5.f));

    sf::Clock clock;
    float dt;
    float maxVelocity = 25.f;
    float speedBackground = 10.f;
     int switchTime = 0;
    int gameStart = 0;
    int pipeSpawnRate = 80;
    int score = 0;
    std::vector<bool> pipesPassed;
    pipesPassed.resize(5, false);

    
    

    //Background
    
    sf::Texture windowText1;
    sf::Texture windowText2;

    windowText1.loadFromFile("Textures/background_movement.png");
    windowText2.loadFromFile("Textures/background_no_movement.png");
    Map background(&windowText1, &windowText2);


    float scaleX1 = static_cast<float>(WINDOWW) / windowText1.getSize().x;
    float scaleY1 = static_cast<float>(WINDOWH) / windowText1.getSize().y;
    float scaleX2 = static_cast<float>(WINDOWW) / windowText2.getSize().x;
    float scaleY2 = static_cast<float>(WINDOWH) / windowText2.getSize().y;

    background.bgScale(scaleX1, scaleY1, scaleX2, scaleY2);

    sf::Vector2f position1(WINDOWW, WINDOWH - background.getSprite1()->getGlobalBounds().height);
    sf::Vector2f position2(0.0f, WINDOWH - background.getSprite2()->getGlobalBounds().height);
    background.bgPosition(position1, position2);

    //Pipe init

    sf::Texture topPipeText;
    topPipeText.loadFromFile("Textures/pipe2.png");

    sf::Texture bottomPipeText;
    bottomPipeText.loadFromFile("Textures/pipe1.png");

    Pipe pipe(&topPipeText, &bottomPipeText, background.getSprite1()->getGlobalBounds().height);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        dt = clock.restart().asSeconds();

        //////////////////////Update

        //Bird init
        if(gameStart==1||gameStart==0)
            bird.animate();

        //Bird movement up-down at the start
        if (!gameStart)
            bird.initFly(dt);
        

        //Bird movement jump 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gameStart == 0) {
            gameStart = 1;
            bird.tap();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gameStart == 1) {
            bird.tap();
        }
       
        
        //Pipe movement
        if(gameStart==1||gameStart==0)
            pipe.movePipes(dt,maxVelocity);

        if (gameStart == 1 && pipeSpawnRate >= 80) {
            pipe.randomPipePosition();
            pipe.createInvisPipe();
            pipe.createBottomPipe();
            pipe.createTopPipe();
            pipe.createScorePipe();
            pipeSpawnRate = 0;
        }
        else if (gameStart == 1 && pipeSpawnRate < 80)
            pipeSpawnRate++;


        //Background movement
        if(gameStart==1||gameStart==0)
            background.bgMove(dt, maxVelocity);

        if(gameStart==1)
            bird.fly(dt);

        //Collision
        sf::Rect<float> r1 = bird.getShape()->getGlobalBounds();
        sf::Rect<float> r2 = background.getSprite1()->getGlobalBounds();
        sf::Rect<float> r3 = background.getSprite2()->getGlobalBounds();
        if (r1.intersects(r2) || r1.intersects(r3)) {
            bird.getShape()->setPosition(bird.getShape()->getPosition().x, bird.getShape()->getPosition().y);
            gameStart = 2;
        }
            
        for (size_t i = 0; i < pipe.getPipes().size(); i++)
        {
            
            sf::Rect<float> raux = pipe.getPipes()[i].getGlobalBounds();
            if (raux.intersects(r1))
                gameStart = 2;
            
       
        }


        for (size_t j = 0; j < pipe.getScorePipes().size(); j++)
        {
            if (pipe.getScorePipes()[j].getPosition().x + pipe.getScorePipes()[j].getGlobalBounds().width < bird.getShape()->getPosition().x+bird.getShape()->getGlobalBounds().width) {
                score++;
                pipe.getScorePipes().erase(pipe.getScorePipes().begin() + j);
            }

        }

        

        if (gameStart == 2) {
            if (r1.intersects(r2) || r1.intersects(r3))
                bird.getShape()->setPosition(bird.getShape()->getPosition().x, bird.getShape()->getPosition().y);
            else
                bird.fall(dt);
        }
         

        //Score
        sf::Text scoreText;
        sf::Font scoreFont;
        scoreFont.loadFromFile("Fonts/04B_19__.ttf");
        scoreText.setFont(scoreFont);
        scoreText.setPosition(WINDOWW / 2, WINDOWH / 8);
        scoreText.setString(std::to_string(score));
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setCharacterSize(60);

        //Draw
        window.clear();
        window.draw(*background.getSprite3());
        
        for (size_t i = 0; i < pipe.getPipes().size(); i++)
        {
            window.draw(pipe.getPipes()[i]);
        }
        window.draw(*background.getSprite1());
        window.draw(*background.getSprite2());
        window.draw(*bird.getShape());
        window.draw(scoreText);

        window.display();
    }

    return 0;
}