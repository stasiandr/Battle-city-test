#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "player_class.h"
#include "bullet_class.h"
#include "map_class.h"

#define MAP_SIZE 8
#define SPRITE_RESOLUTION 64
#define SCREEN_RESOLUTION 512
#define VELOCITY 128
#define BULLET_RESOLUTION 32


int main()
{
	bool can_start = true, win = false; // To check that all images loaded
	sf::RenderWindow window(sf::VideoMode(SCREEN_RESOLUTION, SCREEN_RESOLUTION), "Battle city"); // Set window



	// Loading game textures
	sf::Texture map_texture;
	if (!map_texture.loadFromFile("resources/texture-pack.png")) { // map
		can_start = false;
	}

	sf::Texture player_texture;
	if (!player_texture.loadFromFile("resources/player1.png")) {  // player1
		can_start = false;
	}

	sf::Texture bullet_texture;
	if (!bullet_texture.loadFromFile("resources/bullet.png")) {   // bullet
		can_start = false;
	}
	
	sf::Texture win_texture;
	if (!win_texture.loadFromFile("resources/win-logo.png")) {   // bullet
		can_start = false;
	}

	
	// -------

	// Generating map from using data from map.txt and source from texture-pack.png
	int map_int[MAP_SIZE][MAP_SIZE]; // For collision check later
	sf::Sprite map[MAP_SIZE][MAP_SIZE]; // Sprite matrix
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
			map[i][j] = sprite;
			map_int[i][j] = std::stoi(token);
			i++;
		}
		std::cout << std::endl;
		j++;
	}
	myfile.close();

	Map myMap(map, map_int);
	// -------

	// player1 init
	Player player1;

	player1.setRects(sf::IntRect(0 * SPRITE_RESOLUTION, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION),
		sf::IntRect(2 * SPRITE_RESOLUTION, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION),
		sf::IntRect(1 * SPRITE_RESOLUTION, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION),
		sf::IntRect(3 * SPRITE_RESOLUTION, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION));
	player1.translatePosition(sf::Vector2f(64, 0));
	player1.setSpriteTexture(player_texture);
	player1.changeDirection(DIRECTION::UP);
	// ------
	
	Player player2;

	player2.setRects(sf::IntRect(0 * SPRITE_RESOLUTION, SPRITE_RESOLUTION, SPRITE_RESOLUTION, SPRITE_RESOLUTION),
		sf::IntRect(2 * SPRITE_RESOLUTION, SPRITE_RESOLUTION, SPRITE_RESOLUTION, SPRITE_RESOLUTION),
		sf::IntRect(1 * SPRITE_RESOLUTION, SPRITE_RESOLUTION, SPRITE_RESOLUTION, SPRITE_RESOLUTION),
		sf::IntRect(3 * SPRITE_RESOLUTION, SPRITE_RESOLUTION, SPRITE_RESOLUTION, SPRITE_RESOLUTION));
	player2.translatePosition(sf::Vector2f(SPRITE_RESOLUTION * 6, SPRITE_RESOLUTION * 6));
	player2.setSpriteTexture(player_texture);
	player2.changeDirection(DIRECTION::UP);

	


	std::vector<Bullet> bullet_vec1;
	std::vector<Bullet> bullet_vec2;

	// Setting up delta time = second / FPS. Or delta time = time elapsed since last frame
	sf::Clock clock;
	float delta_time = clock.getElapsedTime().asSeconds();
	clock.restart();
	// ------
	
	// Main cycle
	if (can_start) { // If all textures loaded start game
		while (window.isOpen() && !win)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Space) {
						Bullet bullet;
						bullet.setSpriteTexture(bullet_texture);
						bullet.setRects(sf::IntRect(0 * BULLET_RESOLUTION, 0, BULLET_RESOLUTION, BULLET_RESOLUTION),
							sf::IntRect(2 * BULLET_RESOLUTION, 0, BULLET_RESOLUTION, BULLET_RESOLUTION),
							sf::IntRect(1 * BULLET_RESOLUTION, 0, BULLET_RESOLUTION, BULLET_RESOLUTION),
							sf::IntRect(3 * BULLET_RESOLUTION, 0, BULLET_RESOLUTION, BULLET_RESOLUTION));
						bullet.position = player1.position + sf::Vector2f(SPRITE_RESOLUTION / 2 - BULLET_RESOLUTION/2, SPRITE_RESOLUTION / 2 - BULLET_RESOLUTION / 2);
						bullet.sprite.setPosition(player1.position);
						bullet.setDirection(player1.myDir);
						bullet_vec1.push_back(bullet);
					}

					if (event.key.code == sf::Keyboard::LControl) {
						Bullet bullet;
						bullet.setSpriteTexture(bullet_texture);
						bullet.setRects(sf::IntRect(0 * BULLET_RESOLUTION, 0, BULLET_RESOLUTION, BULLET_RESOLUTION),
							sf::IntRect(2 * BULLET_RESOLUTION, 0, BULLET_RESOLUTION, BULLET_RESOLUTION),
							sf::IntRect(1 * BULLET_RESOLUTION, 0, BULLET_RESOLUTION, BULLET_RESOLUTION),
							sf::IntRect(3 * BULLET_RESOLUTION, 0, BULLET_RESOLUTION, BULLET_RESOLUTION));
						bullet.position = player2.position + sf::Vector2f(SPRITE_RESOLUTION / 2 - BULLET_RESOLUTION / 2, SPRITE_RESOLUTION / 2 - BULLET_RESOLUTION / 2);
						bullet.sprite.setPosition(player2.position);
						bullet.setDirection(player2.myDir);
						bullet_vec2.push_back(bullet);
					}

				}

			}
			window.clear();

			delta_time = clock.getElapsedTime().asSeconds();
			clock.restart();


			myMap.drawMap(window);
			

			for (std::vector<Bullet>::iterator it = bullet_vec1.begin(); it != bullet_vec1.end();) {
				window.draw((*it).getSprite());
				(*it).translatePosition(VELOCITY * 2 * delta_time);
				if ((*it).outsideMap()) {
					bullet_vec1.erase(it);
				}
				else if (myMap.getIdByVec((*it).FrontLeft()) == Map::BLOCKID::ID1) {
					myMap.setBlockByVec(Map::BLOCKID::ID2, (*it).FrontLeft());
					bullet_vec1.erase(it);
				}
				else if (myMap.getIdByVec((*it).FrontRight()) == Map::BLOCKID::ID1) {
					myMap.setBlockByVec(Map::BLOCKID::ID2, (*it).FrontRight());
					bullet_vec1.erase(it);
				}
				else if ((*it).hitPlayer(player2)) {
					win = true;
				}
				else {
					++it;
				}
			}



			for (std::vector<Bullet>::iterator it = bullet_vec2.begin(); it != bullet_vec2.end();) {
				window.draw((*it).getSprite());
				(*it).translatePosition(VELOCITY * 2 * delta_time);
				if ((*it).outsideMap()) {
					bullet_vec2.erase(it);
				}
				else if (myMap.getIdByVec((*it).FrontLeft()) == Map::BLOCKID::ID1) {
					myMap.setBlockByVec(Map::BLOCKID::ID2, (*it).FrontLeft());
					bullet_vec2.erase(it);
				}
				else if (myMap.getIdByVec((*it).FrontRight()) == Map::BLOCKID::ID1) {
					myMap.setBlockByVec(Map::BLOCKID::ID2, (*it).FrontRight());
					bullet_vec2.erase(it);
				}
				else if ((*it).hitPlayer(player1)) {
					win = true;
				}
				else {
					++it;
				}
			}




			window.draw(player1.getSprite());
			window.draw(player2.getSprite());

			// player1

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && 
			    (myMap.getIdByVec(player1.FrontRight(DIRECTION::UP)) == Map::BLOCKID::ID2 &&
				 myMap.getIdByVec(player1.FrontLeft(DIRECTION::UP)) == Map::BLOCKID::ID2)) {
				player1.changeDirection(DIRECTION::UP);
				player1.translatePosition(DIRECTION::UP, VELOCITY * delta_time);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				(myMap.getIdByVec(player1.FrontRight(DIRECTION::DOWN)) == Map::BLOCKID::ID2 &&
				 myMap.getIdByVec(player1.FrontLeft(DIRECTION::DOWN)) == Map::BLOCKID::ID2)) {
				player1.changeDirection(DIRECTION::DOWN);
				player1.translatePosition(DIRECTION::DOWN, VELOCITY * delta_time);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
				(myMap.getIdByVec(player1.FrontRight(DIRECTION::LEFT)) == Map::BLOCKID::ID2 &&
				 myMap.getIdByVec(player1.FrontLeft(DIRECTION::LEFT)) == Map::BLOCKID::ID2)) {
				player1.changeDirection(DIRECTION::LEFT);
				player1.translatePosition(DIRECTION::LEFT, VELOCITY * delta_time);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
				(myMap.getIdByVec(player1.FrontRight(DIRECTION::RIGHT)) == Map::BLOCKID::ID2 &&
				 myMap.getIdByVec(player1.FrontLeft(DIRECTION::RIGHT)) == Map::BLOCKID::ID2)) {
				player1.changeDirection(DIRECTION::RIGHT);
				player1.translatePosition(DIRECTION::RIGHT, VELOCITY * delta_time);
			}

			// player2

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
				(myMap.getIdByVec(player2.FrontRight(DIRECTION::UP)) == Map::BLOCKID::ID2 &&
					myMap.getIdByVec(player2.FrontLeft(DIRECTION::UP)) == Map::BLOCKID::ID2)) {
				player2.changeDirection(DIRECTION::UP);
				player2.translatePosition(DIRECTION::UP, VELOCITY * delta_time);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
				(myMap.getIdByVec(player2.FrontRight(DIRECTION::DOWN)) == Map::BLOCKID::ID2 &&
					myMap.getIdByVec(player2.FrontLeft(DIRECTION::DOWN)) == Map::BLOCKID::ID2)) {
				player2.changeDirection(DIRECTION::DOWN);
				player2.translatePosition(DIRECTION::DOWN, VELOCITY * delta_time);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
				(myMap.getIdByVec(player2.FrontRight(DIRECTION::LEFT)) == Map::BLOCKID::ID2 &&
					myMap.getIdByVec(player2.FrontLeft(DIRECTION::LEFT)) == Map::BLOCKID::ID2)) {
				player2.changeDirection(DIRECTION::LEFT);
				player2.translatePosition(DIRECTION::LEFT, VELOCITY * delta_time);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
				(myMap.getIdByVec(player2.FrontRight(DIRECTION::RIGHT)) == Map::BLOCKID::ID2 &&
					myMap.getIdByVec(player2.FrontLeft(DIRECTION::RIGHT)) == Map::BLOCKID::ID2)) {
				player2.changeDirection(DIRECTION::RIGHT);
				player2.translatePosition(DIRECTION::RIGHT, VELOCITY * delta_time);
			}

			window.display();
		} // End of main cycle
		sf::Clock End_clock;
		while (End_clock.getElapsedTime().asSeconds() < 10) {

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					window.close();
					return 0;
				}
			}

			if (End_clock.getElapsedTime().asSeconds() > 1) {
				window.clear();
				window.draw(sf::Sprite(win_texture));
			}
			window.display();
		}

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