#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 1000
#define MOVE_SPEED 0.2f

using namespace std;

class Terrain {

private:
	sf::Texture ground_image;

public:
	Terrain(); //Constructor

	// The terrain is a collection of rectangleshape chunks
	vector<sf::RectangleShape*> terrain;
	void move(); //chunks move left at a constant speed

	//Heights of each individual chunk, manually coded
	float positions[30] = {
		50,
		20,
		70,
		80,
		100,
		20,
		50,
		50,
		20,
		70,
		80,
		100,
		20,
		50,
		50,
		20,
		70,
		80,
		100,
		20,
		50,
		50,
		20,
		70,
		80,
		100,
		20,
		50,
		50,
		20
	};
};