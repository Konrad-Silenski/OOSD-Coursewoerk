#pragma once
#include "Rocket.h"
#include "Bullet.h"
#include "Enemy.h"
#include<map>
#include<string>
#include <sstream>

class Menu {
	sf::Text menu;
	sf::RenderWindow* window;
	sf::Font font;
	sf::Sprite title;
	sf::Texture hold;

	void initWindow();
	void initTextures();

public:
	Menu();
	virtual ~Menu();

	void run();
	void updatePollEvents();
	void update();
	void render();
};
