#pragma once

#include <map>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::Event sfmlEvent;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//Player
	Player* player;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//Private functions
	void initWindow();
	void initTextures();

	void initPlayer();
	void initEnemies();

public:
	//Constructor /Destructor
	Game();
	virtual ~Game();

	void run();

	void pollEvents();

	void updateInput();
	void updateBullets();
	void updateEnemies();
	void update();
	void render();
};

