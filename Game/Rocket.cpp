#include "Rocket.h"

void Rocket::initVariables()
{
	this->movementSpeed = 4.f;
	this->attackCooldownMax = 25.f;
	this->attackCooldown = this->attackCooldownMax;
	this->vel = 0.f;

	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Rocket::initTexture()
{
	if (!this->texture.loadFromFile("Texture/rocket.png"))
	{
		std::cout << "Error::PLAYER::INITTEXTURE::COULD NOT LOAD TEXTURE"<<"\n";

	}
}


void Rocket::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(350.f, 500.f);

	this->sprite.scale(0.35f, 0.35f);

}

Rocket::Rocket()
{
	
	this->initVariables();
	this->initTexture();
	this->initSprite(); 


}

Rocket::~Rocket()
{

}

const sf::Vector2f& Rocket::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Rocket::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Rocket::getHp() const
{
	return this->hp;
}

const int& Rocket::getHpMax() const
{
	return this->hpMax;
}

void Rocket::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Rocket::setPosition(const float x, const float y)
{
	this->sprite.setPosition( x , y);
}

void Rocket::setHp(const int hp)
{
	this->hp = hp;
}

void Rocket::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Rocket::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Rocket::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Rocket::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Rocket::update()
{
	this->updateAttack();
}

void Rocket::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
