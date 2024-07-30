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
	float moveSpeed;

	void initSprite();
	void initVariables();

public:
	Enemy(float posX, float posY);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;	//Make sure copy not reference or it'll "bug out"

	//Functions

	void update();
	void render(sf::RenderTarget* target);
};

