#include <sfml\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Block.h"
#include "PowerUp.h"

const int SECTION_WIDTH = 10000;
const int NUM_BLOCKS = 30;
const int NUM_POWERUPS = 10;

void ResizeView(sf::RenderWindow& window)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	int newWidth = window.getSize().x;
	sf::Vector2u newSize = sf::Vector2u(newWidth, newWidth * 640 / 1080);
	window.setSize(newSize);
}

void InitObjects(std::vector<Block>& blocks1, std::vector<Block>& blocks2, std::vector<Block>& topBottomBlocks, std::vector<PowerUp>& powerUps1, std::vector<PowerUp>& powerUps2)
{
	blocks1.clear();
	blocks2.clear();
	topBottomBlocks.clear();
	powerUps1.clear();
	powerUps2.clear();

	// top and bottom blocks
	Block top(sf::Vector2f(1100, 100), true);
	Block bottom(sf::Vector2f(1100, 100), true);
	top.body.setPosition(0, 0);
	bottom.body.setPosition(0, 540);
	topBottomBlocks.push_back(top);
	topBottomBlocks.push_back(bottom);

	// blocks that will move
	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		Block block1(sf::Vector2f(50, 80), false);
		block1.body.setPosition(rand() % SECTION_WIDTH, rand() % 460 + 80);
		if (block1.body.getPosition().x > 400)
			blocks1.push_back(block1);

		Block block2(sf::Vector2f(50, 80), false);
		block2.body.setPosition(rand() % SECTION_WIDTH + SECTION_WIDTH, rand() % 460 + 80);
		blocks2.push_back(block2);
	}

	for (int i = 0; i < NUM_POWERUPS; i++)
	{
		PowerUp a(0);
		a.body.setPosition(rand() % SECTION_WIDTH, rand() % 460 + 80);
		if (a.body.getPosition().x > 400)
			powerUps1.push_back(a);
		PowerUp b(1);
		b.body.setPosition(rand() % SECTION_WIDTH, rand() % 460 + 80);
		if (b.body.getPosition().x > 400)
			powerUps1.push_back(b);

		PowerUp c(0);
		c.body.setPosition(rand() % SECTION_WIDTH + SECTION_WIDTH, rand() % 460 + 80);
		powerUps2.push_back(c);
		PowerUp d(1);
		d.body.setPosition(rand() % SECTION_WIDTH + SECTION_WIDTH, rand() % 460 + 80);
		powerUps2.push_back(d);
	}
}

bool CycleObjects(std::vector<Block>& blocks1, std::vector<Block>& blocks2, std::vector<PowerUp>& powerUps1, std::vector<PowerUp>& powerUps2)
{
	if (blocks1[0].body.getPosition().x < blocks2[0].body.getPosition().x)
	{
		for (Block& b : blocks1)
		{
			b.body.setPosition(rand() % SECTION_WIDTH + SECTION_WIDTH, rand() % 460 + 80);
		}
		for (PowerUp& p : powerUps1)
		{
			//p.pickedUp = false;
			p.body.setPosition(rand() % SECTION_WIDTH + SECTION_WIDTH, rand() % 460 + 80);
		}
		return false; // now we are on blocks2
	}
	else {
		for (Block& b : blocks2)
		{
			b.body.setPosition(rand() % SECTION_WIDTH + SECTION_WIDTH, rand() % 460 + 80);
		}
		for (PowerUp& p : powerUps2)
		{
			//p.pickedUp = false;
			p.body.setPosition(rand() % SECTION_WIDTH + SECTION_WIDTH, rand() % 460 + 80);
		}
		return true; // now we are on blocks2
	}
}

void BlockCollision(Player& player, Block b)
{
	if (player.body.getGlobalBounds().intersects(b.body.getGlobalBounds()))
	{
		player.lost = true;
	}
}

void PowerUpCollision(Player& player, float& speed, PowerUp& pu)
{
	if (player.body.getGlobalBounds().intersects(pu.body.getGlobalBounds()))
	{
		pu.pickedUp = true;
		if (pu.type == 0)
		{
			speed += 20.f;
		}
		else if (pu.type == 1)
		{
			speed -= 20.f;
		}
	}
}


sf::Text LoseText(sf::Font& font)
{
	sf::Text text("Try Again", font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Black);
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(540.f, 320.f);
	return text;
}

// MAIN
int main() 
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1080, 640), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);

	Player player;

	float deltaTime = 0.0f;
	sf::Clock clock;

	sf::Font font;
	font.loadFromFile("comic.ttf");
	sf::Text loseText = LoseText(font);

	std::vector<Block> blocks1;
	std::vector<Block> blocks2;
	std::vector<Block> topBottomBlocks;
	std::vector<PowerUp> powerUps1;
	std::vector<PowerUp> powerUps2;
	InitObjects(blocks1, blocks2, topBottomBlocks, powerUps1, powerUps2);


	bool onBlocks1 = true;
	float distance = 0;
	float speed = 200.f;

	while (window.isOpen()) 
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.f / 20.f)
		{
			deltaTime = 1.f / 20.f;
		}

		sf::Event evnt;
		while (window.pollEvent(evnt)) 
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window);
				break;

			case sf::Event::MouseMoved:
				if (player.lost)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
					if (loseText.getGlobalBounds().contains(mousePosF))
					{
						loseText.setFillColor(sf::Color(50, 50, 50));
					}
					else
					{
						loseText.setFillColor(sf::Color(0, 0, 0));
					}
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (player.lost)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
					if (loseText.getGlobalBounds().contains(mousePosF))
					{
						InitObjects(blocks1, blocks2, topBottomBlocks, powerUps1, powerUps2);
						player.Restart();
						distance = 0;
						onBlocks1 = true;
					}
				}
				break;
			}
		}
		if (!player.lost)
		{
			player.Update(deltaTime);
			for (Block& b : blocks1)
			{
				b.Update(deltaTime, speed);
			}
			for (Block& b : blocks2)
			{
				b.Update(deltaTime, speed);
			}
			for (PowerUp& pu : powerUps1)
			{
				pu.Update(deltaTime, speed);
			}
			for (PowerUp& pu : powerUps2)
			{
				pu.Update(deltaTime, speed);
			}
			distance += speed * deltaTime;
		}
		
		std::vector<Block>* currentBlocks;
		std::vector<PowerUp>* currentPUs;
		if (onBlocks1)
		{
			currentBlocks = &blocks1;
			currentPUs = &powerUps1;
		}
		else
		{
			currentBlocks = &blocks2;
			currentPUs = &powerUps2;
		}

		if (distance >= SECTION_WIDTH)
		{
			onBlocks1 = CycleObjects(blocks1, blocks2, powerUps1, powerUps2);
			distance = 0;
		}

		// Check collisions
		for (PowerUp& pu : *currentPUs)
		{
			if (!pu.pickedUp)
			{
				PowerUpCollision(player, speed, pu);
			}
		}
		for (Block& b : *currentBlocks)
		{
			BlockCollision(player, b);
		}
		for (Block& b : topBottomBlocks)
		{
			BlockCollision(player, b);
		}

		window.clear(sf::Color(150, 150, 150));
		player.Draw(window);

		for (Block& b : *currentBlocks)
		{
			b.Draw(window);
		}
		for (Block& b : topBottomBlocks)
		{
			b.Draw(window);
		}
		for (PowerUp& pu : *currentPUs)
		{
			pu.Draw(window);
		}
		
		if (player.lost)
		{
			window.draw(loseText);
		}

		window.display();
	}

	return 0;
}