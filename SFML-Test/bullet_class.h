#pragma once
#include <SFML/Graphics.hpp>
#include "player_class.h"

#define BULLET_RESOLUTION 32
#define SCREEN_RESOLUTION 512

class Bullet {
	sf::IntRect up;
	sf::IntRect down;
	sf::IntRect left;
	sf::IntRect right;
public:
	sf::Sprite sprite;
	sf::Vector2f position;
	DIRECTION dir;

	void setSpriteTexture(sf::Texture &tex) {
		sprite.setTexture(tex);
	}

	sf::Sprite getSprite() {
		return sprite;
	}

	void setDirection(DIRECTION dir_n) {
		dir = dir_n;
		switch (dir)
		{
		case UP:
			sprite.setTextureRect(up);
			break;
		case DOWN:
			sprite.setTextureRect(down);
			break;
		case RIGHT:
			sprite.setTextureRect(right);
			break;
		case LEFT:
			sprite.setTextureRect(left);
			break;
		default:
			break;
		}
	}

	void setRects(sf::IntRect up_n, sf::IntRect down_n, sf::IntRect left_n, sf::IntRect right_n) {
		up = up_n;
		down = down_n;
		left = left_n;
		right = right_n;
	}

	void translatePosition(float vel) {
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

	sf::Vector2f FrontLeft()
	{
		switch (dir)
		{
		case UP:
			return position + sf::Vector2f(0, 0);
			break;
		case DOWN:
			return position + sf::Vector2f(BULLET_RESOLUTION , BULLET_RESOLUTION);
			break;
		case RIGHT:
			return position + sf::Vector2f(BULLET_RESOLUTION, 0);
			break;
		case LEFT:
			return position + sf::Vector2f(0, BULLET_RESOLUTION);
			break;
		default:
			break;
		}
	}

	sf::Vector2f FrontRight()
	{
		switch (dir)
		{
		case UP:
			return position + sf::Vector2f(BULLET_RESOLUTION, 0);
			break;
		case DOWN:
			return position + sf::Vector2f(0, BULLET_RESOLUTION);
			break;
		case RIGHT:
			return position + sf::Vector2f(BULLET_RESOLUTION, BULLET_RESOLUTION);
			break;
		case LEFT:
			return position + sf::Vector2f(0, 0);
			break;
		default:
			break;
		}
	}

	bool outsideMap() {
		switch (dir)
		{
		case UP:
			return position.y < -BULLET_RESOLUTION;
			break;
		case DOWN:
			return position.y > SCREEN_RESOLUTION;
			break;
		case RIGHT:
			return position.x > SCREEN_RESOLUTION;
			break;
		case LEFT:
			return position.x < -BULLET_RESOLUTION;
			break;
		default:
			break;
		}
	}

	bool hitPlayer(Player &p) {
		return FrontLeft().x >= p.position.x && FrontLeft().y >= p.position.y &&
			   FrontLeft().x <= p.position.x + SPRITE_RESOLUTION  && FrontLeft().y <= p.position.y + SPRITE_RESOLUTION ||
			   FrontRight().x >= p.position.x && FrontRight().y >= p.position.y &&
			   FrontRight().x <= p.position.x + SPRITE_RESOLUTION  && FrontRight().y <= p.position.y + SPRITE_RESOLUTION;
	}

};