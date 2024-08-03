#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Enemy
{
private:

protected:
	sf::Sprite sprite;
	sf::Texture spriteTexture;
	std::vector<std::string> enemyTextures;

	float moveSpeed;
	int type;
	int points;

	void initSprite();
	void initVariables(int points, float moveSpeed);

public:
	Enemy();
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;	//Make sure copy not reference or it'll "bug out"
	const int& getPoints() const;
	const sf::Sprite getSprite() const;
	const sf::Vector2f& getCenter() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void move(const float direction, const float moveSpeed);

	//Functions
	virtual void update();	// Virtual means it can get overridden
	void render(sf::RenderTarget* target);
};

