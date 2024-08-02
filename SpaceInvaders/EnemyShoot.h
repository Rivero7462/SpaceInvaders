#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

#include "Bullet.h"
#include "Enemy.h"

class EnemyShoot : public Enemy
{
private:
	int shootCooldown = 10;
	std::vector<Bullet*> bullets;
	sf::Texture bulletTexture;

	//Functions
	void initVariables();
	void initBullet();

public:
	EnemyShoot();
	virtual ~EnemyShoot();

	//Functions

	void update();
	void render(sf::RenderTarget* target);
};

