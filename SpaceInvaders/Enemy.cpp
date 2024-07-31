#include "Enemy.h"

//Private functions
void Enemy::initVariables(int points)
{
	this->points = points;

	this->type = 0;
	this->hpMax = 10;
	this->hp = hpMax;
	this->moveSpeed = 3.0f;
}

void Enemy::initSprite()
{
	this->sprite.setRadius(static_cast<float>(rand() % 20 + 20));
	this->sprite.setPointCount(this->points);

	this->sprite.setFillColor(sf::Color(rand()%255+1, rand() % 255 + 1, rand() % 255 + 1, 255));
}
//Constructors / Destructors

Enemy::Enemy(sf::Vector2f pos, int points)
{
	this->initVariables(points);
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
//Functions

void Enemy::update()
{
	this->sprite.move(0.0f, this->moveSpeed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
