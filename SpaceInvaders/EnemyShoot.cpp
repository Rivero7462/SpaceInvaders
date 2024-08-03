#include "EnemyShoot.h"

void EnemyShoot::initVariables(std::vector<Bullet*>* bullets)
{
	this->shootCooldown = 20;
	this->bullets = bullets;
}

void EnemyShoot::initBullet()
{
	if(!this->bulletTexture.loadFromFile("Textures/Enemy_Bullet.png"))
		std::cout << "ERROR, FAILED TO LOAD ENEMY BULLET TEXTURE\n";
}
//Constructors / Destructors

EnemyShoot::EnemyShoot(std::vector<Bullet*>* bullets, sf::Vector2f position, int points, float moveSpeed)
{
	this->Enemy::initVariables(points, moveSpeed);
	initVariables(bullets);
	initBullet();
	this->initSprite();

	this->setPosition(position);
}

EnemyShoot::~EnemyShoot()
{
}
//Functions

void EnemyShoot::update()
{
	this->Enemy::update();

	this->move(0.0f, this->moveSpeed);

	this->shootCooldown--;

	if (this->shootCooldown <= 0)
	{
		this->bullets->push_back(new Bullet(
			&bulletTexture,
			this->getCenter(),
			sf::Vector2f(1.0f, 1.0f),
			1.0f,
			10.0f,
			1
		));

		this->shootCooldown = 20;
	}
}

