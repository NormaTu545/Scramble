#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
#define BOMB_HEIGHT 25
#define BOMB_WIDTH 10
#define BOMB_SPEED 1.5f
#define LASER_HEIGHT 10
#define LASER_WIDTH 30
#define LASER_SPEED 2.0f

class AttackObject {
//protected means see-able by children of class AttackObject
protected:
	sf::Vector2f position;
	sf::RectangleShape attack_shape;

public:
	AttackObject(); //Constructor

	sf::Texture image;
	sf::Vector2f moveDirection; //Goes RIGHT or goes straight DOWN
	sf::RectangleShape get_shape(); //returns attack_shape for drawing

	void destroy();
	void setUpInstance(sf::Vector2f startPos);
	virtual void move();
};

