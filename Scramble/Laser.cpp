#include "stdafx.h"
#include "Laser.h"

using namespace std;
Laser::Laser(sf::Vector2f spawnPos) {
	moveDirection = *(new sf::Vector2f(1, 0)); //1 in X direction, 0 in Y direction
	setUpInstance(spawnPos);

	//--Set up Laser IMG loading--//
	if (!image.loadFromFile("laser.png")) {
		cout << "Couldn't load laser.png!" << endl;
	}

	//Map image to a RectangleShape instead of a Sprite
	attack_shape.setTexture(&image);
	attack_shape.setSize(sf::Vector2f(LASER_WIDTH, LASER_HEIGHT));
	attack_shape.setPosition(position);
}

void Laser::move() {
	attack_shape.move(moveDirection * LASER_SPEED);

	if (position.x > WINDOW_WIDTH) {
		//Delete instance of laser
		destroy();  
	}
}