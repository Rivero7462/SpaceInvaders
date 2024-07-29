#include "Enemy.h"

//Private functions
void Enemy::initVariables()
{
	this->type		=	 0;
	this->hpMax		=	 10;
	this->hp		=	 hpMax;
	this->damage	=	 1;
	this->points	=	 5;
}

void Enemy::initSprite()
{
	this->sprite.setRadius(static_cast<float>(rand() % 20 + 20));
	this->sprite.setPointCount(static_cast<size_t>(rand() % 8) + 3);

	this->sprite.setFillColor(sf::Color(rand()%255+1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

//Constructors / Destructors
Enemy::Enemy(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
	this->initVariables();
	this->initSprite();
}

Enemy::~Enemy()
{
}
//Functions

void Enemy::update()
{
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
