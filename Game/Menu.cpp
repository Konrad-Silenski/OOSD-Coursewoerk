#include "Menu.h"
#include "Game.h"

void Menu::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Pew Pew Game", sf::Style::Default);
	this->window->setKeyRepeatEnabled(false);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);

}

void Menu::initTextures()
{
	if (!this->font.loadFromFile("Fonts/alagard.ttf"))
		std::cout << "Error::Game::Font" << "\n";

	this->menu.setFont(this->font);
	this->menu.setCharacterSize(36);
	this->menu.setFillColor(sf::Color::White);
	this->menu.setString("Press Enter");
	this->menu.setPosition(305.f, 350.f);

	if (!this->hold.loadFromFile("Texture/title.png"))
	{
		std::cout << "Error::Game::Background" << "\n";
	}
	this->title.setTexture(this->hold);
	this->title.setPosition(75.f, 150.f) ;
}

Menu::Menu()
{
	this->initWindow();
	this->initTextures();
}

Menu::~Menu()
{
	delete this->window;

}

void Menu::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		this->update();
		this->render();
	}
}

void Menu::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Enter) {
			Game game;

			game.run();
		}
	}
}

void Menu::update()
{
	//
}

void Menu::render()
{
	this->window->clear();

	this->window->draw(this->menu);
	this->window->draw(this->title);

	this->window->display();

}
