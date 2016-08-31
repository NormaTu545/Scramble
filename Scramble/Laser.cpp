#include "stdafx.h"
#include "Laser.h"
#include "Player.h"

using namespace std;

Laser::Laser(sf::Vector2f spawnPos) {
	position = spawnPos;
	moveDirection = *(new sf::Vector2f(1, 0));

	if (!laser_image.loadFromFile("laser.png")) {
		cout << "Couldn't load laser.png!" << endl;
	}

	//Map image to a RectangleShape instead of a Sprite
	laser_shape.setTexture(&laser_image);
	laser_shape.setSize(sf::Vector2f(LASER_WIDTH, LASER_HEIGHT));
	laser_shape.setPosition(position);
}

void Laser::move() {
	//RectangleShape's move function
	laser_shape.move(moveDirection * LASER_SPEED);
	//Updates position.x
	position.x += (moveDirection.x*LASER_SPEED);
}

sf::RectangleShape* Laser::getShape() {
	return &laser_shape;
}