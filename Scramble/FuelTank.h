#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Terrain.h"

#define FUEL_TANK_HEIGHT 70
#define FUEL_TANK_WIDTH 45
#define FUEL_SCORE_REWARD 150
#define FUEL_AMOUNT 25

using namespace std;

class FuelTank {

private:
	sf::Vector2f* position;
	sf::Texture fuel_image;
	sf::RectangleShape fuel_shape;

public:
	FuelTank(float startX, float startY); //Constructor
	sf::FloatRect get_position(); //will use for collision detection
	sf::RectangleShape* get_shape(); //passes copy of shape for drawing

	void go_away(); //Teleports fuel tank offscreen 
					//My lazy solution to deleting this instance
	void come_back(sf::Vector2f start_position); //Teleports back onscreen for game restart
	void move(); //Moves object left to scroll with the terrain
};