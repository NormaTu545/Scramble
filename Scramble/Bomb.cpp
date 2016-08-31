#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb(sf::Vector2f spawnPos) {
	position = spawnPos;
	moveDirection = *(new sf::Vector2f(0, 1));

	if (!bomb_image.loadFromFile("bomb.png")) {
		cout << "Couldn't load bomb.png!" << endl;
	}

	//Map image to a RectangleShape instead of a Sprite
	bomb_shape.setTexture(&bomb_image);
	bomb_shape.setSize(sf::Vector2f(BOMB_WIDTH, BOMB_HEIGHT));
	bomb_shape.setPosition(position);
}

void Bomb::move() {
	//RectangleShape's move function
	bomb_shape.move(moveDirection * BOMB_SPEED);
	//Updates position.y
	position.y += (moveDirection.y * BOMB_SPEED);
}

sf::RectangleShape* Bomb::getShape() {
	return &bomb_shape;
}