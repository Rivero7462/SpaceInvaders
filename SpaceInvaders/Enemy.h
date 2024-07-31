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
	int points;
	float moveSpeed;

	void initSprite();
	void initVariables(int points);

public:
	Enemy(sf::Vector2f pos, int points);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;	//Make sure copy not reference or it'll "bug out"
	const int& getPoints() const;

	//Functions

	void update();
	void render(sf::RenderTarget* target);
};

