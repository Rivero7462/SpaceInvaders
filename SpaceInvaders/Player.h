#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "iostream"

class Player
{
private:
	//Variables
	float movementSpeed;
	int maxShootCooldown;
	int shootCooldown;

	sf::Texture texture;
	sf::Sprite sprite;

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPlayerCenter() const;
	const bool& canShoot();

	//Functions
	void move(const float dirX, const float dirY);

	void updateCooldown();
	void update();
	void render(sf::RenderTarget& target);
};

