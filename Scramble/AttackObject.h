#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
#define BOMB_HEIGHT 25
#define BOMB_WIDTH 10
#define BOMB_SPEED 1.5f

class AttackObject {
//protected means see-able by children of class AttackObject
protected:


public:
	AttackObject(); //Constructor
	
	//virtual sf::RectangleShape get_shape(); //returns attack_shape for drawing

	void destroy();
	void setUpInstance(sf::Vector2f startPos);
	virtual void move();
};

