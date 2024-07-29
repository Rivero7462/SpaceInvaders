#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "iostream"

class Bullet
{
	sf::Vector2f direction;
	float movementSpeed;

	sf::Sprite sprite;

	//Private Functions

private:

public:
	Bullet();
	Bullet(sf::Texture* texture, sf::Vector2f pos, sf::Vector2f size, float dirY, float movementSpeed);
	virtual ~Bullet();

	//Accessor
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);

};

