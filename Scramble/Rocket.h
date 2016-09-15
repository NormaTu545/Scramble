#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Terrain.h"

#define ROCKET_HEIGHT 70
#define ROCKET_WIDTH 50
#define ROCKET_SPEED 0.5f
#define ROCKET_SCORE_REWARD 50
#define FLYING_ROCKET_SCORE_REWARD 100
#define TRIGGER_DISTANCE 200

using namespace std;

class Rocket {

private:
	sf::Vector2f* position;
	sf::Texture rocket_image;
	sf::Texture flying_image;
	sf::RectangleShape rocket_shape;
	bool rocket_flying = false; //for toggling the two rocket image textures

public:
	sf::Vector2f moveDirection; //0 in X direction, 1 in Y direction

	Rocket(float startX, float startY); //Constructor
	sf::FloatRect get_position(); //for collision detection
	sf::RectangleShape* get_shape(); //passes copy of shape for drawing

	bool rocket_flying_state(); //returns rocket_flying
	void set_rocket_flying_state(bool b); //resets to !rocket_flying
	void go_away(); //Teleports saucer offscreen 
	void come_back(sf::Vector2f start_position); //Teleports back onscreen for game restart
	void fly_up(); //Sends rocket flying upwards in attack mode
	void move(); //Moves object left to scroll with the terrain
};