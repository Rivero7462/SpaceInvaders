#include "Enemy.h"
#include <iostream>

//Private functions
void Enemy::initVariables(int points, float moveSpeed)
{
	this->points = points;
	this->moveSpeed = moveSpeed;
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
//Modifiers

void Enemy::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Enemy::move(const float direction, const float moveSpeed)
{
	this->sprite.move(direction, moveSpeed);
}

//Functions

void Enemy::update()
{

}

void Enemy::render(sf::RenderTarget* target)
{
	//std::cout << "RENDERING\n";
	target->draw(this->sprite);
}
