#include "Enemy.h"
#include <iostream>

//Private functions
void Enemy::initVariables(int type)
{
	this->type = type;
	this->points = type;
	this->moveSpeed = 3.0f;
}

void Enemy::initSprite()
{
	//Set Texture
	std::string path = "Textures/Enemy_Ship_" + std::to_string(this->type) + ".png";

	if (this->spriteTexture.loadFromFile(path))
		this->sprite.setTexture(this->spriteTexture);
	else
		std::cout << "ERROR FAILED TO LOAD ENEMY TEXTURE" << std::endl;

	this->sprite.rotate(180.0f);
}
//Constructors / Destructors

Enemy::Enemy()
{
	this->type = 0;
	this->points = 0;
	this->moveSpeed = 0;
}

Enemy::Enemy(sf::Vector2f pos, int type)
{
	this->initVariables(type);
	this->initSprite();

	this->sprite.setPosition(pos);
}

Enemy::~Enemy()
{
}
//Accessors

const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
const int& Enemy::getPoints() const
{
	return this->points;
}
const sf::Sprite Enemy::getSprite() const
{
	return this->sprite;
}
const sf::Vector2f& Enemy::getCenter() const
{
	float centerX = this->sprite.getPosition().x + (this->sprite.getGlobalBounds().width / 2);
	float centerY = this->sprite.getPosition().y + (this->sprite.getGlobalBounds().height / 2);

	return sf::Vector2f(centerX, centerY);
}
//Functions

void Enemy::update()
{
	this->sprite.move(0.0f, this->moveSpeed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
