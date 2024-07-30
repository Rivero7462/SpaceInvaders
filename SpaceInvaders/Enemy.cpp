#include "Enemy.h"

//Private functions
void Enemy::initVariables()
{
	this->type = 0;
	this->hpMax = 10;
	this->hp = hpMax;
	this->damage = 1;
	this->points = 5;
	this->moveSpeed = 3.0f;
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
	this->initVariables();
	this->initSprite();

	this->sprite.setPosition(posX, posY);
}

Enemy::~Enemy()
{
}
//Accessors

const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
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
