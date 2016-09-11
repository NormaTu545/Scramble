#include "stdafx.h"
#include "Rocket.h"

Rocket::Rocket(float startX, float startY) {
	//Passes by REFERENCE
	position = new sf::Vector2f(startX, startY);

	//--Set up fuel tank IMG loading--//
	if (!rocket_image.loadFromFile("rocket.png")) {
		cout << "Couldn't load rocket.png!" << endl;
	}

	//Map image to a RectangleShape instead of a Sprite
	rocket_shape.setTexture(&rocket_image);
	rocket_shape.setSize(sf::Vector2f(ROCKET_WIDTH, ROCKET_HEIGHT));
	rocket_shape.setPosition(*position);
}

sf::RectangleShape* Rocket::get_shape() {
	sf::RectangleShape* pointer = &rocket_shape;
	return pointer;
}