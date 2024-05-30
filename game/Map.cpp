#include "Map.h"

Map::Map(sf::Texture* bg_no_movement, sf::Texture* bg_movement) {
	this->windowText1=*bg_movement;
	this->windowText2 = *bg_no_movement;
	this->windowSprite1.setTexture(windowText2);
	this->windowSprite2.setTexture(windowText2);
	this->windowSprite3.setTexture(windowText1);
	this->speedBackground = 10.f;
}

void Map::bgScale(float scaleX1, float scaleY1, float scaleX2,float scaleY2) {
	this->windowSprite1.setScale(scaleX1, scaleY1 / 5.5f);
	this->windowSprite2.setScale(scaleX1, scaleY1 / 5.5f);
	this->windowSprite3.setScale(scaleX2, scaleY2);
}

void Map::bgPosition(sf::Vector2f position1, sf::Vector2f position2) {
	this->windowSprite1.setPosition(position1);
	this->windowSprite2.setPosition(position2);
}

void Map::bgMove(float dt, float maxVelocity) {
	this->windowSprite1.move(-speedBackground * dt * maxVelocity, 0);
	this->windowSprite2.move(-speedBackground * dt * maxVelocity, 0);
	if (this->windowSprite1.getPosition().x + WINDOWW < 0) {
		this->windowSprite1.setPosition(this->windowSprite2.getPosition().x + WINDOWW, this->windowSprite2.getPosition().y);
	}
	if (this->windowSprite2.getPosition().x + WINDOWW < 0) {
		this->windowSprite2.setPosition(this->windowSprite1.getPosition().x + WINDOWW, this->windowSprite1.getPosition().y);
	}
}

sf::Sprite* Map::getSprite1() { return &windowSprite1; }

sf::Sprite* Map::getSprite2() { return &windowSprite2; }

sf::Sprite* Map::getSprite3() { return &windowSprite3; }