#include "Player.h"

void Player::initVariables()
{
	this->maxHp = 10;
	this->hp = maxHp;
	this->maxShootCooldown = 10;
	this->shootCooldown = 0;
	this->movementSpeed = 10.0f;
}

//Private Functions
void Player::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/Player_Ship.png"))
		std::cout << "FAILED TO LOAD PLAYER TEXTURE" << std::endl;
}

void Player::initSprite()
{
	//Set texture to sprite
	this->sprite.setTexture(this->texture);
	
	this->sprite.scale(0.25f, 0.25f);
}

Player::Player()
{
	this->initVariables();

	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}
//Accessors

const sf::Vector2f& Player::getPlayerCenter() const
{
	float centerX = this->sprite.getPosition().x + (this->sprite.getGlobalBounds().width / 2);
	float centerY = this->sprite.getPosition().y + (this->sprite.getGlobalBounds().height / 2);

	return sf::Vector2f(centerX, centerY);
}

const sf::FloatRect& Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const bool& Player::canShoot()
{
	if (this->shootCooldown == 0)
	{
		shootCooldown = maxShootCooldown;
		return true;
	}
	else
		return false;
}
const int& Player::getHealth() const
{
	return this->hp;
}
const int& Player::getMaxHealth() const
{
	return this->maxHp;
}
//Modifiers

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::takeDamage(int damage)
{
	if(this->hp > 0)
		this->hp -= damage;

	if(this->hp < 0)
		this->hp = 0;
}
//Functions

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::updateCooldown()
{
	if (this->shootCooldown > 0)
		this->shootCooldown--;
}

void Player::update()
{
	this->updateCooldown();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
