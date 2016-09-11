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

sf::FloatRect Saucer::get_position() {
	return saucer_shape.getGlobalBounds();
}

sf::RectangleShape* Saucer::get_shape() {
	sf::RectangleShape* pointer = &saucer_shape;
	return pointer;
}

void Saucer::go_away() {
	position->y = -10000; //instantly goes way the hell offscreen
	saucer_shape.setPosition(*position); //Actually update position
}