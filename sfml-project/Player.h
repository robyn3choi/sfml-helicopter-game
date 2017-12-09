#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player();
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision();
	sf::Vector2f GetPosition() { return body.getPosition(); }
	void Restart();

	sf::RectangleShape body;
	bool lost;


private:

	sf::Texture texture;
	float acceleration = 3000.f;
	sf::Vector2f velocity;
};

