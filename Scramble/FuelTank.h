#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define FUEL_TANK_HEIGHT 70
#define FUEL_TANK_WIDTH 45
#define SCORE_REWARD 150
#define FUEL_AMOUNT 25

using namespace std;

class FuelTank {

private:
	sf::Vector2f* position;
	sf::Texture fuel_image;
	sf::RectangleShape fuel_shape;

public:
	FuelTank(float startX, float startY); //Constructor

	sf::RectangleShape* get_shape(); //passes copy of shape for drawing
};