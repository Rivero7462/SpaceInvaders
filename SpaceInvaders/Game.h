#pragma once

#include <map>
//#include <string>
#include <sstream>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyShoot.h"

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::Event sfmlEvent;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;

	//World
	sf::Texture backgroundTex;
	sf::Sprite backgroundSprite;
	float scrollSpeed;
	float backgroundY;

	//Systems
	unsigned int points;

	//Player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//Private functions
	void initVariables();
	void initWindow();
	void initTextures();
	void initWorld();
	void initGUI();
	void initSystems();

	void initPlayer();
	void initEnemies();

public:
	//Constructor /Destructor
	Game();
	virtual ~Game();

	void run();

	void pollEvents();

	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void update();

	void renderGUI();
	void renderWorld();
	void render();
};