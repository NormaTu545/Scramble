#include "stdafx.h"
#include "Saucer.h"

Saucer::Saucer(float startX, float startY) {
	//Passes by REFERENCE
	position = new sf::Vector2f(startX, startY);

	//--Set up fuel tank IMG loading--//
	if (!saucer_image.loadFromFile("saucer.png")) {
		cout << "Couldn't load saucer.png!" << endl;
	}

	//Map image to a RectangleShape instead of a Sprite
	saucer_shape.setTexture(&saucer_image);
	saucer_shape.setSize(sf::Vector2f(SAUCER_WIDTH, SAUCER_HEIGHT));
	saucer_shape.setPosition(*position);
}

sf::RectangleShape* Saucer::get_shape() {
	sf::RectangleShape* pointer = &saucer_shape;
	return pointer;
}