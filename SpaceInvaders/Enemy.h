#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Enemy
{
private:
	sf::Sprite sprite;
	sf::Texture spriteTexture;
	std::vector<std::string> enemyTextures;

	int type;
	int points;
	float moveSpeed;

	void initSprite();
	void initVariables(int points);

public:
	Enemy();
	Enemy(sf::Vector2f pos, int type);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;	//Make sure copy not reference or it'll "bug out"
	const int& getPoints() const;
	const sf::Sprite getSprite() const;
	const sf::Vector2f& getCenter() const;

	//Functions

	void update();
	void render(sf::RenderTarget* target);
};

