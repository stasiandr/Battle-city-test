#pragma once
#include <SFML/Graphics.hpp>


#define MAP_SIZE 8
#define SPRITE_RESOLUTION 64

class Map {
	sf::Sprite map_sprites[MAP_SIZE][MAP_SIZE];
	int map_ints[MAP_SIZE][MAP_SIZE];
public:
	enum BLOCKID { ID1, ID2 };
	Map(sf::Sprite _map_sprites[MAP_SIZE][MAP_SIZE], int _map_ints[MAP_SIZE][MAP_SIZE]) {
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				map_sprites[i][j] = _map_sprites[i][j];
				map_ints[i][j] = _map_ints[i][j];
			}
		}
	}

	void drawMap(sf::RenderWindow &window) {
		for (int i = 0; i != MAP_SIZE; i++) // Drawing map
		{
			for (int j = 0; j != MAP_SIZE; j++)
			{
				window.draw(map_sprites[i][j]);
			}
		}
	}

	sf::IntRect getRectById(BLOCKID id) {
		switch (id)
		{
		case Map::ID1:
			return sf::IntRect(0, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION);
			break;
		case Map::ID2:
			return sf::IntRect(SPRITE_RESOLUTION, 0, SPRITE_RESOLUTION, SPRITE_RESOLUTION);
			break;
		default:
			break;
		}
	}
	int getIntById(BLOCKID id) {
		switch (id)
		{
		case Map::ID1:
			return 1;
			break;
		case Map::ID2:
			return 0;
			break;
		default:
			break;
		}
	}
	BLOCKID getIdByInt(int id) {
		switch (id)
		{
		case 1:
			return ID1;
			break;
		default:
			return ID2;
			break;
		}
	}

	void setBlockById(BLOCKID id, int i, int j) {
		map_sprites[i][j].setTextureRect(getRectById(id));
		map_ints[i][j] = getIntById(id);
	}
	void setBlockByVec(BLOCKID id, sf::Vector2f pos) {
		map_sprites[((int)pos.x)/SPRITE_RESOLUTION][((int)pos.y)/SPRITE_RESOLUTION].setTextureRect(getRectById(id));
		map_ints[((int)pos.x) / SPRITE_RESOLUTION][((int)pos.y) / SPRITE_RESOLUTION] = getIntById(id);
	}

	BLOCKID getIdByVec(sf::Vector2f pos) {
		return getIdByInt(map_ints[((int)pos.x) / SPRITE_RESOLUTION][((int)pos.y) / SPRITE_RESOLUTION]);
	}

};