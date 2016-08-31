#pragma once

#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>
#define BOMB_HEIGHT 30
#define BOMB_WIDTH 15
#define BOMB_SPEED 0.25f //Slower than laser speed

using namespace std;

class Bomb {

public:
	Bomb(sf::Vector2f spawnPos); //Constructor

	sf::Vector2f position;
	sf::RectangleShape bomb_shape;
	sf::Texture bomb_image;
	sf::Vector2f moveDirection; //0 in X direction, 1 in Y direction
	sf::RectangleShape* getShape(); //returns pointer for drawing

	void move(); //Goes straight down
};