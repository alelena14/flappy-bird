#include "Pipe.h"
#define WINDOWW 1000 //x
#define WINDOWH 900  //y
#define PIPE_SPAWN_SPEED 10.f


    Pipe::Pipe(sf::Texture* topPipeText, sf::Texture* bottomPipeText, int minYPos) {
        this->topPipeText = topPipeText;
        this->bottomPipeText = bottomPipeText;
        this->randomYPosition = 0.f;
        this->minYPos = minYPos;
    };

    void Pipe::createTopPipe() {
        sf::Sprite pipe;
        pipe.setTexture(*topPipeText);
        pipe.setPosition(WINDOWW, -1.2f * pipe.getGlobalBounds().height - randomYPosition);
        pipe.setScale(4.f, 3.6f);
        pipeSprites.push_back(pipe);
    }

    void Pipe::createBottomPipe() {
        sf::Sprite pipe;
        pipe.setTexture(*bottomPipeText);
        pipe.setScale(4.f, 3.6f);
        pipe.setPosition(WINDOWW, WINDOWH - 0.4f*pipe.getGlobalBounds().height - randomYPosition);
        pipeSprites.push_back(pipe);
    }
    void Pipe::createInvisPipe() {
        sf::Sprite pipe;
        pipe.setTexture(*topPipeText);
        pipe.setPosition(WINDOWW, pipe.getGlobalBounds().height);
        pipe.setScale(0.5f, 0.5f);
        pipe.setColor(sf::Color(0, 0, 0, 0));
        pipeSprites.push_back(pipe);
    }
    void Pipe::createScorePipe() {
        sf::Sprite pipe;
        pipe.setTexture(*topPipeText);
        pipe.setPosition(WINDOWW, pipe.getGlobalBounds().height);
        pipe.setScale(4.f, 3.6f);
        pipe.setColor(sf::Color(0,0,0,0));
        scorePipeSprites.push_back(pipe);
    }
    void Pipe::movePipes(float dt, float maxVelocity) {
        for (size_t i = 0; i < pipeSprites.size(); i++)
        {
            float speed = PIPE_SPAWN_SPEED * dt * maxVelocity;
            pipeSprites[i].move(-speed, 0);
            sf::Vector2f pipePosition = pipeSprites[i].getPosition();
            if (pipePosition.x + pipeSprites[i].getGlobalBounds().width < 0)
                pipeSprites.erase(pipeSprites.begin() + i);
        }
        for (size_t i = 0; i < scorePipeSprites.size(); i++)
        {
            float speed = PIPE_SPAWN_SPEED * dt * maxVelocity;
            scorePipeSprites[i].move(-speed, 0);
            sf::Vector2f pipePosition = scorePipeSprites[i].getPosition();
            if (pipePosition.x + pipeSprites[i].getGlobalBounds().width < 0)
                scorePipeSprites.erase(scorePipeSprites.begin() + i);
        }
    }

    void Pipe::randomPipePosition() {
        randomYPosition = rand() % (minYPos + 1);
    }

   

    const std::vector<sf::Sprite>& Pipe::getPipes() const { return pipeSprites; }

     std::vector<sf::Sprite>& Pipe::getScorePipes()  { return scorePipeSprites; }

