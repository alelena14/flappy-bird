#ifndef PIPE_H
#define PIPE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

class Pipe {
private:
    std::vector<sf::Sprite> pipeSprites;
    std::vector<sf::Sprite> scorePipeSprites;
    sf::Texture* topPipeText;
    sf::Texture* bottomPipeText;
    float randomYPosition;
    int minYPos;

public:
    Pipe(sf::Texture* topPipeText, sf::Texture* bottomPipeText, int minYPos);

    void createTopPipe();

    void createBottomPipe();

    void createInvisPipe();

    void createScorePipe();

    void movePipes(float dt, float maxVelocity);

    void randomPipePosition();

    const std::vector<sf::Sprite>& getPipes() const;

     std::vector<sf::Sprite>& getScorePipes() ;

};

#endif // !PIPE_H

