#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "iostream"

class Bullet
{
private:
	sf::Vector2f direction;
	float movementSpeed;
	int type;

	sf::Sprite sprite;

public:
	Bullet();
	Bullet(sf::Texture* texture, sf::Vector2f pos, sf::Vector2f size, float dirY, float movementSpeed, int type);
	virtual ~Bullet();

	//Accessor
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);

};

