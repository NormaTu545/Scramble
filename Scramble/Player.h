#pragma once

#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
#define SHIP_WIDTH 75
#define SHIP_HEIGHT 50

class Player {

private:
	sf::Vector2f position;
	sf::Texture player_image;
	sf::RectangleShape player_shape;

	const float ship_speed = 1.0f;

public:
	Player(float startX, float startY); //Constructor
	float fireRateTimer = 0;

	sf::FloatRect get_position(); //will use for collision detection
	sf::RectangleShape* get_shape(); //passes copy of shape for drawing
	sf::RectangleShape* fire_laser(); //sets up laser & returns ptr for drawing
	//sf::RectangleShape* drop_bomb();

	void move_up(); //adds ship_speed to y position
	void move_down(); //subtracts ship_speed from y position
	void move_left(); //subtracts ship_speed from x position
	void move_right(); //adds ship_speed to x position

	void update(); //updates ship position

	//getLives 
	//decrement_Lives
};