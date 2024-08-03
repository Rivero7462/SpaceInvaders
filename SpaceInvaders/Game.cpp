#include "Game.h"

void Game::initVariables()
{
	scrollSpeed = 2.0f;
	backgroundY = 0.0f;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Space Invaders", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/Player_Bullet.png");
}

void Game::initWorld()
{
	if (this->backgroundTex.loadFromFile("Textures/background.png"))
		this->backgroundSprite.setTexture(this->backgroundTex);
	else
		std::cout << "ERROR LOADING BACKGROUND\n";

	this->backgroundTex.setRepeated(true);
}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/almostserious.ttf"))
		std::cout << "ERROR COULDN'T LOAD FONT\n";

	//Init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(24);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setPosition(20.0f, 0.0f);

	//Game over text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::White);
	this->gameOverText.setString("GAME OVER");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.0f - this->gameOverText.getGlobalBounds().width / 2.0f,
		this->window->getSize().y / 2.0f - this->gameOverText.getGlobalBounds().height / 2.0f);

	//Init Player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.0f, 25.0f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.0f, 40.0f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(sf::Vector2f(this->window->getSize().x / 2.0f - this->player->getBounds().width / 2.0f, this->window->getSize().y - 100.0f));
}

void Game::initEnemies()
{
	this->spawnTimerMax = 40.0f;
	this->spawnTimer = this->spawnTimerMax;
}

//Constructor /Destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initTextures();
	this->initWorld();
	this->initGUI();
	this->initSystems();

	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto &i : this->textures)
		delete i.second;

	//Bullets
	for (auto *i : this->bullets)
		delete i;

	//Enemies
	for (auto* i : this->enemies)
		delete i;

}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->pollEvents();

		if (this->player->getHealth() > 0)
		{
			this->update();
			this->render();
		}
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateInput()
{
	//Move Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.0, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.0, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.0, -1.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.0, 1.0f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canShoot())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPlayerCenter(),
				sf::Vector2f(0.1f, 0.1f),
				-1.0f,
				30.0f,
				0
			));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n";
	this->pointText.setString(ss.str());

	//Update Player GUI
	float hpPercent = static_cast<float>(this->player->getHealth()) / this->player->getMaxHealth();
	this->playerHpBar.setSize(sf::Vector2f(300.0f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{
	backgroundY += scrollSpeed;

	if (backgroundY >= this->backgroundTex.getSize().y)
		backgroundY = 0.0f;
}

void Game::updateCollision()
{
	//Screen bounds collision
	if (this->player->getBounds().left < 0.0f)
		this->player->setPosition(sf::Vector2f(0.0f, this->player->getBounds().top));
	if (this->player->getBounds().left + this->player->getBounds().width > this->window->getSize().x)
		this->player->setPosition(sf::Vector2f(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top));
	if (this->player->getBounds().top < 0.0f)
		this->player->setPosition(sf::Vector2f(this->player->getBounds().left, 0.0f));
	if (this->player->getBounds().top + this->player->getBounds().height > this->window->getSize().y)
		this->player->setPosition(sf::Vector2f(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height));
}

void Game::updateBullets()
{
	unsigned counter = 0;

	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet Culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.0f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	// Spawn enemy
	this->spawnTimer += 0.5f;

	if (this->spawnTimer >= spawnTimerMax)
	{
		int enemyType = rand() % 3;
		int screenSpace = static_cast<int>(this->window->getSize().x - 50.0f);
		sf::Vector2f position(rand() % screenSpace + 50.0f, -100.0f);

		switch (enemyType)
		{
		case 0:
			//this->enemies.push_back(new Enemy(position, 1, 3.0f));
			this->enemies.push_back(new EnemyShoot(&bullets, position, 1, 3.0f));
			break;
		case 1:
			this->enemies.push_back(new EnemyShoot(&bullets, position, 1, 3.0f));
			break;
		case 2:
			this->enemies.push_back(new EnemyShoot(&bullets, position, 1, 3.0f));
			break;
		}
		this->spawnTimer = 0.0f;
	}

	// For each enemy
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		this->enemies[i]->update();

		bool enemy_removed = false;

		// For each bullet
		for (size_t k = 0; k < this->bullets.size() && !enemy_removed; k++)
		{
			// Enemy Shot
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				enemy_removed = true;
			}
		}

		// Player collide with enemy
		if (!enemy_removed && this->enemies[i]->getBounds().intersects(this->player->getBounds()))
		{
			this->player->takeDamage(3);
			this->enemies.erase(this->enemies.begin() + i);
			enemy_removed = true;
		}

		// Enemy culling (bottom of screen)
		if (!enemy_removed && this->enemies[i]->getBounds().top > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			enemy_removed = true;
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateGUI();

	this->updateWorld();
}

void Game::renderGUI()
{
	//Order decides layers
	this->window->draw(this->pointText);

	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	// Draw the background twice to create the looping effect
	this->backgroundSprite.setPosition(0, backgroundY);
	this->window->draw(this->backgroundSprite);
	this->backgroundSprite.setPosition(0, backgroundY - this->backgroundTex.getSize().y);
	this->window->draw(this->backgroundSprite);
}

void Game::render()
{
	this->window->clear();

	// Draw World
	this->renderWorld();

	// Draw stuff
	this->player->render(*this->window);

	//Bullets
	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	//Enemies
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	//GUI
	this->renderGUI();

	if (this->player->getHealth() <= 0)
		this->window->draw(this->gameOverText);

	// Display stuff
	this->window->display();
}
