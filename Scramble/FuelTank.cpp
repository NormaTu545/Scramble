#include "stdafx.h"
#include "FuelTank.h"


FuelTank::FuelTank(float startX, float startY) {
	//Passes by REFERENCE
	position = new sf::Vector2f(startX, startY);

	//--Set up fuel tank IMG loading--//
	if (!fuel_image.loadFromFile("fuelTank.png")) {
		cout << "Couldn't load fuelTank.png!" << endl;
	}

	//Map image to a RectangleShape instead of a Sprite
	fuel_shape.setTexture(&fuel_image);
	fuel_shape.setSize(sf::Vector2f(FUEL_TANK_WIDTH, FUEL_TANK_HEIGHT));
	fuel_shape.setPosition(*position);
}

sf::RectangleShape* FuelTank::get_shape() {
	sf::RectangleShape* pointer = &fuel_shape;
	return pointer;
}