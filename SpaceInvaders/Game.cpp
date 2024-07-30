#include "Game.h"

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

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/almostserious.ttf"))
		std::cout << "ERROR COULDN'T LOAD FONT\n";

	//Init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(24);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 40.0f;
	this->spawnTimer = this->spawnTimerMax;
}

//Constructor /Destructor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
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
		this->update();
		this->render();
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
				player->getPlayerCenter(),
				sf::Vector2f(0.1f, 0.1f),
				-1.0f,
				30.0f
			));
	}
}

void Game::updateGUI()
{

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

			std::cout << this->bullets.size() << "\n";
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
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.0f, -100.0f));
		this->spawnTimer = 0.0f;
	}

	// For each enemy
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_removed = false;
		this->enemies[i]->update();

		// Removing enemy
		if (!enemy_removed)
		{
			// If shot remove enemy and bullet
			for (size_t k = 0; k < this->bullets.size() && !enemy_removed; k++)
			{
				if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds()))
				{
					this->bullets.erase(this->bullets.begin() + k);
					this->enemies.erase(this->enemies.begin() + i);
					enemy_removed = true;
				}
			}

			// Enemy culling (bottom of screen)
			if (this->enemies[i]->getBounds().top > this->window->getSize().y)
			{
				this->enemies.erase(this->enemies.begin() + i);
				std::cout << this->enemies.size() << "\n";
				enemy_removed = true;
			}
		}
	}

	//Update each enemy
	for (auto* enemy : this->enemies)
	{
		enemy->update();
	}
}

void Game::update()
{
	this->pollEvents();

	this->updateInput();

	this->player->update();

	this->updateBullets();

	this->updateEnemies();

	this->updateGUI();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
}

void Game::render()
{
	this->window->clear();

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

	// Display stuff
	this->window->display();
}
