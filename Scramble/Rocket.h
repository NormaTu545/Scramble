#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define ROCKET_HEIGHT 70
#define ROCKET_WIDTH 50
#define SCORE_REWARD 50
#define FLYING_REWARD 100

using namespace std;

class Rocket {

private:
	sf::Vector2f* position;
	sf::Texture rocket_image;
	sf::RectangleShape rocket_shape;

public:
	Rocket(float startX, float startY); //Constructor

	sf::RectangleShape* get_shape(); //passes copy of shape for drawing
};