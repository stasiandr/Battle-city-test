#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "player_class.h"

#define MAP_SIZE 8
#define SPRITE_RESOLUTION 64
#define SCREEN_RESOLUTION 512
#define VELOCITY 128

int main()
{
	bool can_start = true; // To check that all images loaded
	sf::RenderWindow window(sf::VideoMode(SCREEN_RESOLUTION, SCREEN_RESOLUTION), "Battle city"); // Set window


	// Loading game textures
	sf::Texture map_texture;
	if (!map_texture.loadFromFile("resources/texture-pack.png")) { // map
		can_start = false;
	}

	sf::Texture player_texture;
	if (!player_texture.loadFromFile("resources/player1.png")) { // player
		can_start = false;
	}
	// -------

	// Generating map from using data from map.txt and source from texture-pack.png
	int map_int[MAP_SIZE][MAP_SIZE]; // For collision check later
	std::vector<std::vector<sf::Sprite>> map(MAP_SIZE); // Sprite matrix
	int j = 0;
	std::string line;
	std::ifstream myfile("resources/map.txt"); //Map looks like bool matrix now, fix later
	for (std::string line; std::getline(myfile, line);)
	{
		int i = 0;
		std::istringstream iss(line);
		for (std::string token; iss >> token; ) {
			std::cout << token << " ";
			sf::Sprite sprite;
			sprite.setTexture(map_texture);
			switch (std::stoi(token))
			{
				case 1:
					sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION));
					break;
				default:
					sprite.setTextureRect(sf::IntRect(SPRITE_RESOLUTION, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION));
					break;
			}
			sprite.setPosition(sf::Vector2f(i*SPRITE_RESOLUTION, j*SPRITE_RESOLUTION));
			map[i].push_back(sprite);
			map_int[i][j] = std::stoi(token);
			i++;
		}
		std::cout << std::endl;
		j++;
	}
	myfile.close();
	// -------

	// Player init
	Player player;

	player.setRects(sf::IntRect(0 * SPRITE_RESOLUTION, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION),
					 sf::IntRect(2 * SPRITE_RESOLUTION, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION),
					 sf::IntRect(1 * SPRITE_RESOLUTION, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION),
					 sf::IntRect(3 * SPRITE_RESOLUTION, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION));
	player.position = sf::Vector2f(0, 0);
	player.setSpriteTexture(player_texture);
	player.changeDirection(Player::UP);
	// ------

	// Setting up delta time = second / FPS. Or delta time = time elapsed since last frame
	sf::Clock clock;
	float delta_time = clock.getElapsedTime().asSeconds();
	clock.restart();
	// ------
	
	// Main cycle
	if (can_start) { // If all textures loaded start game
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			delta_time = clock.getElapsedTime().asSeconds();
			clock.restart();

			for (int i = 0; i != MAP_SIZE; i++) // Drawing map
			{
				for (int j = 0; j != MAP_SIZE; j++)
				{
					window.draw(map[i][j]);
				}
			} 
			window.draw(player.getSprite());

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				player.changeDirection(Player::UP);
				player.translatePosition(0, -VELOCITY * delta_time);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				player.changeDirection(Player::DOWN);
				player.translatePosition(0, VELOCITY * delta_time);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				player.changeDirection(Player::LEFT);
				player.translatePosition(-VELOCITY * delta_time, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				player.changeDirection(Player::RIGHT);
				player.translatePosition(VELOCITY * delta_time, 0);
			}

			window.display();
		} // End of main cycle
	} else { // Display errors in console for debug
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.display();
		}
	}


	return 0;
}