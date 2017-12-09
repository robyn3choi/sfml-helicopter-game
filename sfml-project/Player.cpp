#include "Player.h"


Player::Player()
{
	body.setSize(sf::Vector2f(80.f, 68.f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	texture.loadFromFile("head.png");
	body.setTexture(&texture);
	lost = false;
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		velocity.y -= acceleration * deltaTime;
	}

	velocity.y += 981.0f * deltaTime;

	body.move(velocity * deltaTime);

	
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision()
{
	printf("lost");
}

void Player::Restart()
{
	body.setPosition(206.0f, 206.0f);
	velocity = sf::Vector2f(0, 0);
	lost = false;
}
