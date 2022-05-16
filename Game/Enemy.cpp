#include "Enemy.h"

void Enemy::initVariables()
{
	 this->pointCount = rand() % 8 + 3;
	 this->type = 0;
	 this->speed = static_cast<float>(this->pointCount/2.5);
	 this->hp = this->hpMax;
	 this->hpMax = static_cast<int>(this->pointCount);
	 this->damage = this->pointCount + 5;
	 this->points = this->pointCount;

}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 4);
	this->shape.setOrigin((this->pointCount * 4 / 2.5), (this->pointCount * 4 / 2.5));
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(NULL));
	this->shape.setOutlineThickness(2);
	this->shape.setOutlineColor(sf::Color(rand() & 255, rand() & 255, rand() & 255, 255));
	this->shape.setRotation(100);


}

Enemy::Enemy(float pos_x, float pos_y)
{
	
	this->initVariables();
	this->initShape();

	this->shape.setPosition(pos_x, pos_y);
	
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}


void Enemy::update()
{
	this->shape.move(0.f, this->speed);
	this->shape.rotate(1.f);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);

}
