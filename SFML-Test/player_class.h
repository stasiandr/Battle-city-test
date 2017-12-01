#pragma once
#include <SFML/Graphics.hpp>
#define SPRITE_RESOLUTION 64

class Player {
	sf::IntRect up;
	sf::IntRect down;
	sf::IntRect left;
	sf::IntRect right;
public:
	enum DIRECTION { UP, DOWN, RIGHT, LEFT };
	sf::Vector2f position;
	sf::Sprite sprite;
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
		switch (dir)
		{
		case Player::UP:
			sprite.setTextureRect(up);
			break;
		case Player::DOWN:
			sprite.setTextureRect(down);
			break;
		case Player::RIGHT:
			sprite.setTextureRect(right);
			break;
		case Player::LEFT:
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

	void translateToDirection(Player::DIRECTION dir) {

	}


};
