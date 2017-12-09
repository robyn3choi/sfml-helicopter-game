#pragma once
#include <sfml\Graphics.hpp>

class Block
{
public:
	Block(sf::Vector2f size, bool isWall);
	~Block();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime, float speed);


public:
	sf::RectangleShape body;


private:
	bool isWall;
};

