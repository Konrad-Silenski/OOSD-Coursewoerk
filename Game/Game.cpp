#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Pew Pew Game", sf::Style::Default);
	this->window->setKeyRepeatEnabled(false);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);

}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Texture/bullet.png");
	
}

void Game::initGUI()
{
	this->gameOver = false;
	this->earthMaxHP = 100;
	this->earthHP = 100;

	if (!this->font.loadFromFile("Fonts/alagard.ttf"))
		std::cout << "Error::Game::Font" << "\n";

	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(26);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");
	this->pointText.setPosition(325.f, 530.f);

	this->health.setFont(this->font);
	this->health.setCharacterSize(26);
	this->health.setFillColor(sf::Color::White);
	this->health.setString("Ship health:");
	this->health.setPosition(10.f, 530.f);

	this->earthHealth.setFont(this->font);
	this->earthHealth.setCharacterSize(26);
	this->earthHealth.setFillColor(sf::Color::White);
	this->earthHealth.setString("Earth:");
	this->earthHealth.setPosition(715.f, 530.f);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(64);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f - 50.f);

	this->GUIback.setSize(sf::Vector2f(800.f, 65.f));
	this->GUIback.setFillColor(sf::Color::Black);
	this->GUIback.setPosition(sf::Vector2f(0.f, 535.f));

	this->hpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setOutlineThickness(2);
	this->hpBar.setOutlineColor(sf::Color::Yellow);
	this->hpBar.setPosition(sf::Vector2f(10.f, 565.f));
	this->hpBarBack = this->hpBar;
	this->hpBarBack.setFillColor(sf::Color::Black);

	this->earthBar.setSize(sf::Vector2f(300.f, 25.f));
	this->earthBar.setFillColor(sf::Color::Red);
	this->earthBar.setOutlineThickness(2);
	this->earthBar.setOutlineColor(sf::Color::Yellow);
	this->earthBar.setPosition(sf::Vector2f(490.f, 565.f));
	this->earthBarBack = this->earthBar;
	this->earthBarBack.setFillColor(sf::Color::Black);


}

void Game::initWorld()
{
	if (this->backgroundTex.loadFromFile("Texture/background.jpg"))
	{
		std::cout << "Error::Game::Background" << "\n";
	}
	this->background.setTexture(this->backgroundTex);
	this->background.scale(1.25f, 1.5f);

}

void Game::initSystems()
{
	this->points - 0;
}

void Game::initRocket()
{
	this->rocket = new Rocket();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 70.f;
	this->spawnTimer = 0.1f;
	this->timer = 10.f;
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initRocket();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->rocket;
	
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	for (auto* i : this->bullets)
	{
		delete i;
	}

	for (auto* i : this->enemies)
	{
		delete i;
	}

}

void Game::run()
{
	this->mode = "MENU";

	while (this->window->isOpen()) 
	{
		this->updatePollEvents();

		if (this->rocket->getHp() > 0 && this->earthHP > 0)
			this->update();
		else {
			this->gameOver = true;
			this->update();
		}

		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
			if (gameOver) {
				if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Space)
					this->window->close();
			}
	}
}

void Game::updateInput()
{
	if (!gameOver) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->rocket->move(-1.5f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->rocket->move(1.5f, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->rocket->canAttack())
		{
			this->bullets.push_back(
				new Bullet(this->textures["BULLET"],
					this->rocket->getPos().x + this->rocket->getBounds().width / 4.f - 1,
					this->rocket->getPos().y - 25,
					0.f, -1.f, 5.f)
			);

		}
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());

	if (!gameOver) {
		float hpPercent = static_cast<float>(this->rocket->getHp()) / this->rocket->getHpMax();
		this->hpBar.setSize(sf::Vector2f(300 * hpPercent, this->hpBar.getSize().y));

		float earthPer = static_cast<float>(this->earthHP) / this->earthMaxHP;
		this->earthBar.setSize(sf::Vector2f(300 * earthPer, this->earthBar.getSize().y));
	}

}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	if (!gameOver) {
		if (this->rocket->getBounds().left < 0.f)
		{
			this->rocket->setPosition(0.f, this->rocket->getBounds().top);
		}

		else if (this->rocket->getBounds().left + this->rocket->getBounds().width >= this->window->getSize().x)
		{
			this->rocket->setPosition(this->window->getSize().x - this->rocket->getBounds().width, this->rocket->getBounds().top);
		}

		if (this->rocket->getBounds().top < 0.f)
		{
			this->rocket->setPosition(this->rocket->getBounds().left, 0.f);
		}

		else if (this->rocket->getBounds().top + this->rocket->getBounds().height >= this->window->getSize().y)
		{
			this->rocket->setPosition(this->rocket->getBounds().left, this->window->getSize().y - this->rocket->getBounds().height);
		}
	}
}

void Game::updateBullets()
{
	if (!gameOver) {
		unsigned counter = 0;
		for (auto* bullet : this->bullets)
		{
			bullet->update();

			if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
			{
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
			}
			++counter;
		}
	}

}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) 
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f + 20, -10.f));
		if (this->spawnTimerMax > this->timer) {
			this->spawnTimerMax -= 0.10f;
		}
		this->spawnTimer = 0.f;
	}

	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		if (enemy->getBounds().top > this->window->getSize().y)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			this->earthHP -= 10;
		}
		else if(enemy->getBounds().intersects(this->rocket->getBounds()))
		{
			this->rocket->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			
		}

		++counter;
	}
	
		

}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				if (!gameOver)
					this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();
	if (!gameOver)
		this->rocket->update();
	this->updateCollision();
	if (!gameOver)
		this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->GUIback);
	this->window->draw(this->pointText);
	this->window->draw(this->health);
	this->window->draw(this->earthHealth);
	this->window->draw(this->hpBarBack);
	this->window->draw(this->hpBar);
	this->window->draw(this->earthBarBack);
	this->window->draw(this->earthBar);
}

void Game::renderWorld()
{
	this->window->draw(this->background);
}

void Game::render()
{
	this->window->clear();

	this->renderWorld();

	if (!gameOver)
		this->rocket->render(*this->window);

	if (!gameOver)
		for (auto* bullet : this->bullets)
		{
			bullet->render(this->window);
		}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	if (this->rocket->getHp() <= 0 || this->earthHP <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();
}
