#pragma once

#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>
#define LASER_HEIGHT 10
#define LASER_WIDTH 30
#define LASER_SPEED 2.0f

class Laser {

public:
	Laser(sf::Vector2f spawnPos); //Constructor

	sf::Vector2f position;
	sf::RectangleShape laser_shape;
	sf::Texture laser_image;
	sf::Vector2f moveDirection; //1 in X direction, 0 in Y direction
	sf::RectangleShape* getShape(); //returns pointer for drawing

	void move(); //Goes right
};