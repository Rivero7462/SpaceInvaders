#include "EnemyShoot.h"

void EnemyShoot::initVariables()
{
	this->shootCooldown = 10;
}
void EnemyShoot::initBullet()
{
	if(!this->bulletTexture.loadFromFile("Textures/Enemy_Bullet.png"))
		std::cout << "ERROR, FAILED TO LOAD ENEMY BULLET TEXTURE\n";
}
//Constructors / Destructors

EnemyShoot::EnemyShoot()
{
	initVariables();
}

EnemyShoot::~EnemyShoot()
{
	//Bullets
	for (auto* i : this->bullets)
		delete i;
}
//Functions

void EnemyShoot::update()
{
	this->shootCooldown--;

	if (this->shootCooldown <= 0)
	{
		std::cout << "Shoot\n";

		this->bullets.push_back(
			new Bullet(
				&bulletTexture,
				this->getCenter(),
				sf::Vector2f(0.1f, 0.1f),
				1.0f,
				10.0f,
				1
			));
		this->shootCooldown = 10;
	}
}

void EnemyShoot::render(sf::RenderTarget* target)
{
	//target->draw()
}
