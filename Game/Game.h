#pragma once
#include "Rocket.h"
#include "Bullet.h"
#include "Enemy.h"
#include<map>
#include<string>
#include <sstream>


class Game
{
private:

	std::string mode;
	std::string menu = "Start Game";
	
	sf::RenderWindow* window;

	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	sf::Font font;
	sf::Text pointText;
	sf::Text health;
	sf::Text earthHealth;

	sf::Text gameOverText;

	sf::Texture backgroundTex;
	sf::Sprite background;

	unsigned points;

	Rocket* rocket;

	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape earthBar;
	sf::RectangleShape earthBarBack;
	sf::RectangleShape GUIback;

	float spawnTimer;
	float spawnTimerMax;
	float timer;
	float earthHP;
	float earthMaxHP;
	std::vector<Enemy*> enemies;

	bool gameOver;

	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();
	void initRocket();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	void run();
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();
	void renderGUI();
	void renderWorld();
	void render();
};

