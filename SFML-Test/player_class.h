#pragma once
#include <SFML/Graphics.hpp>
#define SPRITE_RESOLUTION 64
#define SPRITE_DELTA 4
enum DIRECTION { UP, DOWN, RIGHT, LEFT };
class Player {
	sf::IntRect up;
	sf::IntRect down;
	sf::IntRect left;
	sf::IntRect right;
public:
	sf::Vector2f position;
	sf::Sprite sprite;
	DIRECTION myDir;
	bool moving;

	void setSpriteTexture(sf::Texture &tex) {
		sprite.setTexture(tex);
	}

	void setRects(sf::IntRect up_n, sf::IntRect down_n, sf::IntRect left_n, sf::IntRect right_n) {
		up = up_n;
		down = down_n;
		left = left_n;
		right = right_n;
	}

	void changeDirection(DIRECTION dir) {
		myDir = dir;
		switch (dir)
		{
		case DIRECTION::UP:
			sprite.setTextureRect(up);
			break;
		case DIRECTION::DOWN:
			sprite.setTextureRect(down);
			break;
		case DIRECTION::RIGHT:
			sprite.setTextureRect(right);
			break;
		case DIRECTION::LEFT:
			sprite.setTextureRect(left);
			break;
		default:
			break;
		}
	}

	sf::Sprite getSprite() {
		return sprite;
	}
	
	void translatePosition(sf::Vector2f delta) {
		position += delta;
		sprite.setPosition(position);
	}

	void translatePosition(float x, float y) {
		position.x += x;
		position.y += y;
		sprite.setPosition(position);
	}

	void translatePosition(DIRECTION dir, float vel) {
		switch (dir)
		{
		case DIRECTION::UP:
			position.y -= vel;
			break;
		case DIRECTION::DOWN:
			position.y += vel;
			break;
		case DIRECTION::RIGHT:
			position.x += vel;
			break;
		case DIRECTION::LEFT:
			position.x -= vel;
			break;
		default:
			break;
		}
		sprite.setPosition(position);
	}

	sf::Vector2f FrontLeft(DIRECTION _dir)
	{
		switch (_dir)
		{
		case UP:
			return position + sf::Vector2f(0 + SPRITE_DELTA, 0 + SPRITE_DELTA);
			break;
		case DOWN:
			return position + sf::Vector2f(SPRITE_RESOLUTION - SPRITE_DELTA, SPRITE_RESOLUTION - SPRITE_DELTA);
			break;
		case RIGHT:
			return position + sf::Vector2f(SPRITE_RESOLUTION - SPRITE_DELTA, 0 + SPRITE_DELTA);
			break;
		case LEFT:
			return position + sf::Vector2f(0 + SPRITE_DELTA, SPRITE_RESOLUTION - SPRITE_DELTA);
			break;
		default:
			break;
		}
	}

	sf::Vector2f FrontRight(DIRECTION _dir)
	{
		switch (_dir)
		{
		case UP:
			return position + sf::Vector2f(SPRITE_RESOLUTION - SPRITE_DELTA, 0 + SPRITE_DELTA);
			break;
		case DOWN:
			return position + sf::Vector2f(0 + SPRITE_DELTA, SPRITE_RESOLUTION - SPRITE_DELTA);
			break;
		case RIGHT:
			return position + sf::Vector2f(SPRITE_RESOLUTION - SPRITE_DELTA, SPRITE_RESOLUTION - SPRITE_DELTA);
			break;
		case LEFT:
			return position + sf::Vector2f(0 + SPRITE_DELTA, 0 + SPRITE_DELTA);
			break;
		default:
			break;
		}
	}


};
