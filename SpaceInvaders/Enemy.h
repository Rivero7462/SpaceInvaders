#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Enemy
{
private:
	sf::CircleShape sprite;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initSprite();
	void initVariables();

public:
	Enemy();
	virtual ~Enemy();

	//Functions

	void update();
	void render();
};

