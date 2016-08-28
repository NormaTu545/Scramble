#include "stdafx.h"
#include "Player.h"
#include "Laser.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
#define SHIP_WIDTH 75
#define SHIP_HEIGHT 50

using namespace std;

//--Constructor here---------------------------------------------
Player::Player(float startX, float startY) {
	position.x = startX;
	position.y = startY;

	//--Set up player IMG loading--//
	if (!player_image.loadFromFile("player.png")) {
		cout << "Couldn't load player.png!" << endl;
	}

	//Map image to a RectangleShape instead of a Sprite
	player_shape.setTexture(&player_image);
	player_shape.setSize(sf::Vector2f(SHIP_WIDTH, SHIP_HEIGHT));
	player_shape.setPosition(position);
}

sf::FloatRect Player::get_position() {
	return player_shape.getGlobalBounds();
}

sf::RectangleShape* Player::get_shape() {
	sf::RectangleShape* p = &player_shape;
	return p;
}

sf::RectangleShape Player::fire_laser() {
	/*
	* Calls AttackObject Laser.move(ship.x, ship.y) to x=WINDOW_WIDTH
	* If laser collides with enemy, grant points and delete enemy instance
	*/
	sf::FloatRect currPos = Player::get_position();
	sf::Vector2f ship_right_side(currPos.left + SHIP_WIDTH, currPos.top);
	Laser pew(ship_right_side); //Spawn laser at right of image

	return pew.get_shape();
}
/*
sf::RectangleShape Player::drop_bomb() {

}
*/
void Player::move_up() {
	position.y -= ship_speed;
}

void Player::move_down() {
	position.y += ship_speed;
}

void Player::move_left() {
	position.x -= ship_speed;
}

void Player::move_right() {
	position.x += ship_speed;
}

void Player::update() {
	player_shape.setPosition(position);

	//Lock position of our spaceship to stay onscreen.
	if (position.y < 0) {
		position.y = 0;
	}
	else if (position.y + SHIP_HEIGHT > WINDOW_HEIGHT) {
		position.y = WINDOW_HEIGHT - SHIP_HEIGHT;
	}
	
	if (position.x < 0) {
		position.x = 0;
	}
	else if (position.x + SHIP_WIDTH > WINDOW_WIDTH) {
		position.x = WINDOW_WIDTH - SHIP_WIDTH;
	}
}