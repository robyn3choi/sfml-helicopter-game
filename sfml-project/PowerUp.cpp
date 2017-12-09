#include "PowerUp.h"


PowerUp::PowerUp(int type)
{
	pickedUp = false;
	this->type = type;
	body = sf::RectangleShape(sf::Vector2f(60.f, 60.f));
	if (type == 0)
	{
		body.setFillColor(sf::Color::Red);
	}
	else if (type == 1)
	{
		body.setFillColor(sf::Color::Blue);
	}
}


PowerUp::~PowerUp()
{
}

void PowerUp::Draw(sf::RenderWindow & window)
{
	if (!pickedUp)
	{
		window.draw(body);
	}
}

void PowerUp::Update(float deltaTime, float speed)
{
	if (!pickedUp)
	{
		float distance = -speed*deltaTime;
		body.move(distance, 0);
	}
}
