#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

#include "Bullet.h"
#include "Enemy.h"

class EnemyShoot : public Enemy
{
private:
	int shootCooldown = 10;
	std::vector<Bullet*>* bullets;
	sf::Texture bulletTexture;

	//Functions
	void initVariables(std::vector<Bullet*>* bullets);
	void initBullet();

public:
	EnemyShoot(std::vector<Bullet*> *bullets, sf::Vector2f position, int points, float moveSpeed);
	virtual ~EnemyShoot();

	//Functions

	void update();
};

