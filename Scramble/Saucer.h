#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#define SAUCER_HEIGHT 70
#define SAUCER_WIDTH 80
#define SAUCER_SCORE_REWARD 200

using namespace std;

class Saucer {

private:
	sf::Vector2f* position;
	sf::Texture saucer_image;
	sf::RectangleShape saucer_shape;

public:
	Saucer(float startX, float startY); //Constructor
	sf::FloatRect get_position(); //will use for collision detection
	sf::RectangleShape* get_shape(); //passes copy of shape for drawing
	void go_away(); //Teleports saucer offscreen 

};