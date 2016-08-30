#pragma once
//#include "AttackObject.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>
#define LASER_HEIGHT 10
#define LASER_WIDTH 30
#define LASER_SPEED 2.0f

class Laser {

	
public:
	sf::Vector2f position;
	sf::RectangleShape attack_shape;
	sf::Texture image;
	sf::Vector2f moveDirection; //Goes RIGHT or goes straight DOWN
	Laser(sf::Vector2f spawnPos);
	sf::RectangleShape* getShape();
	void move();
};