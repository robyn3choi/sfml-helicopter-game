#include "Block.h"


Block::Block(sf::Vector2f size, bool isWall)
{
	this->isWall = isWall;
	body = sf::RectangleShape(size);
	body.setFillColor(sf::Color::Black);
}


Block::~Block()
{
}

void Block::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Block::Update(float deltaTime, float speed)
{
	// if this block is not a wall, then move it to the left
	if (!isWall)
	{
		float distance = -speed*deltaTime;
		body.move(distance, 0);
	}
}
