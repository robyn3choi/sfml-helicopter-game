#pragma once
#include <sfml\Graphics.hpp>

class PowerUp
{
public:
	PowerUp(int type);
	~PowerUp();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime, float speed);


public:
	sf::RectangleShape body;
	int type; // 0 = fast, 1 = slow, 2 = barrier?
	bool pickedUp;
};

