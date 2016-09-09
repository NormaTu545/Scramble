#include "stdafx.h"
#include "Player.h"
#include "Laser.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

//--Constructor here---------------------------------------------

Player::Player(float startX, float startY) {
	//Passes by REFERENCE
	position = new sf::Vector2f(startX, startY);
	justDied = false;

	//--Set up player IMG loading--//
	if (!player_image.loadFromFile("player.png")) {
		cout << "Couldn't load player.png!" << endl;
	}

	//Map image to a RectangleShape instead of a Sprite
	player_shape.setTexture(&player_image);
	player_shape.setSize(sf::Vector2f(SHIP_WIDTH, SHIP_HEIGHT));
	player_shape.setPosition(*position);
}

sf::Vector2f Player::get_position() {
	//sf::Vector2f newVect(player_shape.);
	return *(position);
}

void Player::setPosition(sf::Vector2f new_position) {
	position -> x = new_position.x;
	position -> y = new_position.y;
}

sf::RectangleShape* Player::get_shape() {
	sf::RectangleShape* pointer = &player_shape;
	return pointer;
}

void Player::move_up() {
	position -> y -= ship_speed;
}

void Player::move_down() {
	position -> y += ship_speed;
}

void Player::move_left() {
	position -> x -= ship_speed;
}

void Player::move_right() {
	position -> x += ship_speed;
}

void Player::die() {
	player_shape.rotate(35);
}

void Player::update() {
	player_shape.setPosition(*position);
	fireRateTimer += 0.1f; //counts how many frames have passed

	//Lock position of our spaceship to stay onscreen.
	if (position -> y < 0) {
		position ->y = 0;
	}
	else if (position -> y + SHIP_HEIGHT > WINDOW_HEIGHT) {
		position -> y = WINDOW_HEIGHT - SHIP_HEIGHT;
	}
	
	if (position ->x < 0) {
		position -> x = 0;
	}
	else if (position -> x + SHIP_WIDTH > WINDOW_WIDTH) {
		position -> x = WINDOW_WIDTH - SHIP_WIDTH;
	}
}