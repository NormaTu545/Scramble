#include "stdafx.h"
#include "Rocket.h"

Rocket::Rocket(float startX, float startY) {
	//Passes by REFERENCE
	position = new sf::Vector2f(startX, startY);
	moveDirection = *(new sf::Vector2f(0, -1));

	//--Resting Rocket IMG loading--//
	if (!rocket_image.loadFromFile("rocket.png")) {
		cout << "Couldn't load rocket.png!" << endl;
	}

	//--Flying Rocket IMG loading--//
	if (!flying_image.loadFromFile("rocketFly.png")) {
		cout << "Couldn't load rocket.png!" << endl;
	}

	//Map image to a RectangleShape instead of a Sprite
	rocket_shape.setTexture(&rocket_image);
	rocket_shape.setSize(sf::Vector2f(ROCKET_WIDTH, ROCKET_HEIGHT));
	rocket_shape.setPosition(*position);
}

sf::FloatRect Rocket::get_position() {
	return rocket_shape.getGlobalBounds();
}

sf::RectangleShape* Rocket::get_shape() {
	sf::RectangleShape* pointer = &rocket_shape;
	return pointer;
}

void Rocket::go_away() {
	position->y = -10000; //instantly goes way the hell offscreen
	rocket_shape.setPosition(*position); //Actually update position
}

void Rocket::come_back(sf::Vector2f start_position) {
	//The rectangleShape is repositioned back onscreen
	*position = start_position;
	rocket_shape.setPosition(*position);
}

void Rocket::fly_up() {
	//Switch image texture to flying rocket & offset height for the flames
	rocket_shape.setTexture(&flying_image);
	rocket_shape.setSize(sf::Vector2f(ROCKET_WIDTH, ROCKET_HEIGHT + 20));

	//RectangleShape's move function
	rocket_shape.move(moveDirection * ROCKET_SPEED);
	//Updates position.x
	position->y -= (moveDirection.y * ROCKET_SPEED); 
}

void Rocket::move() {
	sf::Vector2f dir(-1 * MOVE_SPEED, 0);
	rocket_shape.move(dir);
}