#include "Bullet.h"

//Constructors / Destructors
Bullet::Bullet()
{
	this->movementSpeed = 0;
	this->type = 0;
}

Bullet::Bullet(sf::Texture* texture, sf::Vector2f pos, sf::Vector2f size, float dirY, float movementSpeed, int type)
{
	//Set texture to sprite
	this->sprite.setTexture(*texture);
	this->sprite.scale(size);
	this->sprite.setPosition(pos.x - this->sprite.getGlobalBounds().width / 2, pos.y - this->sprite.getGlobalBounds().height / 2);
	
	this->direction.y = dirY;
	this->movementSpeed = movementSpeed;
	this->type = type;
}

Bullet::~Bullet()
{

}
//Functions

const sf::FloatRect Bullet::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Bullet::update()
{
	//Movement
	this->sprite.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
