// Scramble.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Player.h"
#include "Laser.h"
#include "Bomb.h"
#include "FuelTank.h"
#include "Saucer.h"
#include "Rocket.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
#define FUEL_BAR_XPOS 635
#define FUEL_LOSS_RATE 0.0025f

using namespace std;

int main() {
	
	vector<Laser*> lasers;
	vector<Bomb*> bombs;
	bool game_over = false;
	bool fuel_tank_destroyed = false;
	bool rocket_destroyed = false;
	bool saucer_destoryed = false;
	float current_fuel = 100; //Start 100% Full
	int player_lives = 3; //Start with 3 lives
	int score = 0;
	sf::Vector2f death_position;  //Save point where player died

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Scramble_Game");
	
	//--[Loading Game Stuff]-----------------------------------------------------------------

	// [Heads Up Display set up]
	sf::Text score_text;
	sf::Text fuel_text;

	//Font is "karmatic_arcade" from dafont.com
	sf::Font font;
	font.loadFromFile("kaFont.ttf");

	score_text.setFont(font);
	score_text.setCharacterSize(35);
	score_text.setPosition(10.0f, 0.0f);
	score_text.setColor(sf::Color::White);

	fuel_text.setFont(font);
	fuel_text.setCharacterSize(35);
	fuel_text.setPosition(WINDOW_WIDTH / 2, 0.0f);
	fuel_text.setColor(sf::Color::White);
	fuel_text.setString("FUEL");

	sf::RectangleShape greyBar(sf::Vector2f(360, 40));
	greyBar.setPosition(FUEL_BAR_XPOS - 5, 5);
	greyBar.setFillColor(sf::Color::Color(200, 200, 200, 100));

	sf::RectangleShape fuelBar(sf::Vector2f(355, 35));
	fuelBar.setPosition(FUEL_BAR_XPOS - 3, 7);
	fuelBar.setFillColor(sf::Color::Color(0, 255, 150, 150));

	// [Lives set up]
	sf::Texture playerIMG;

	if (!playerIMG.loadFromFile("player.png")) {
		cout << "Couldn't load player.png!" << endl;
		return EXIT_FAILURE;
	}

	vector<sf::RectangleShape*> lives;

	for (int total_lives = 0; total_lives < player_lives; total_lives++) {
		sf::RectangleShape* player_life_img = new sf::RectangleShape(sf::Vector2f(50.0f, 40.0f));
		player_life_img ->setTexture(&playerIMG);
		lives.push_back(player_life_img);
	}

	//Load & Set Up Background
	sf::Texture outer_space;

	if (!outer_space.loadFromFile("space.jpg")) {
		cout << "Couldn't load space.jpg!" << endl;
		return EXIT_FAILURE;
	}

	sf::Sprite background;
	background.setTexture(outer_space);
	
	/* Scale background manually to fit the window */
	background.setScale(1.6f, 1.5f);
	
	/* Make a player */
	Player player(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2);
	sf::Vector2f player_position = player.get_position();

	/* Make a TEST Fuel Tank, Saucer, & Rocket */
	FuelTank fuelTank(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
	Saucer saucer(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 100);
	Rocket rocket(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 4 + 150);

	//[Actual Game Loop]--------------------------------------------------

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//~~[KEY EVENT HANDLING]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player.move_up();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player.move_down();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player.move_left();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player.move_right();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			current_fuel -= 0.5; //for testing
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			//Fires a laser & adds that instance to lasers vector
			if (player.fireRateTimer >= 5) { //Every 50 frames. 5/0.1 = 50
				sf::Vector2f ship_right_side(player.get_position().x + SHIP_WIDTH,
										     player.get_position().y + SHIP_HEIGHT / 2);

				Laser* pew = new Laser(ship_right_side); //Spawn laser at right of image
				//Add to list of lasers
				lasers.push_back(pew);
				player.fireRateTimer = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			//Drops a bomb & adds that instance to bombs vector 
			if (player.fireRateTimer >= 10) { //Every 100 frames. 10/0.1 = 100
				//sf::FloatRect currPos = player.get_position();
				sf::Vector2f ship_bottom_side(player.get_position().x + SHIP_WIDTH / 2, 
											  player.get_position().y + SHIP_HEIGHT);

				Bomb* boom = new Bomb(ship_bottom_side); //Spawn laser at bottom of image
				//Adds this instance to list of bombs
				bombs.push_back(boom);
				player.fireRateTimer = 0; //resets timer
			}
		}

		/*
		*********************************************************************
		[Event Handling]
		*********************************************************************
		*/
		
		/* HANDLE LASER DESTROYING FUEL TANK */

		for (int i = 0; i < lasers.size(); i++) {
			bool hit_fuel_tank = (*lasers[i]).laser_shape.getGlobalBounds().intersects(fuelTank.get_position());
			if (hit_fuel_tank) {
				current_fuel += FUEL_AMOUNT;
				score += FUEL_SCORE_REWARD;
				fuelTank.go_away();

				delete(lasers[i]); //laser instance is now null ptr
				lasers.erase(lasers.begin() + i); //deletes null ptr
				fuel_tank_destroyed = true;
			}
		}

		/* HANDLE BOMB DESTROYING FUEL TANK */

		for (int j = 0; j < bombs.size(); j++) {
			bool hit_fuel_tank = (*bombs[j]).bomb_shape.getGlobalBounds().intersects(fuelTank.get_position());
			if (hit_fuel_tank) {
				current_fuel += FUEL_AMOUNT;
				score += FUEL_SCORE_REWARD;
				fuelTank.go_away();

				delete(bombs[j]); //bomb instance is now null ptr
				bombs.erase(bombs.begin() + j); //deletes null ptr
				fuel_tank_destroyed = true;
			}
		}


		//~~~~~~~~~~~~~~~~~~~~~[WINDOW UPDATE]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

		window.clear();

		//--------DRAW REGARDLESS OF GAME OVER OR NOT OVER-------------

		player.update();
		window.draw(background);

		//Score update
		stringstream score_stream;
		score_stream << "SCORE  " << score;
		score_text.setString(score_stream.str());

		//Lives indicator update
		for (int l = 0; l < lives.size(); l++) {
			lives[l]->setPosition(sf::Vector2f(10 + l * 55.0f, 45.0f));
			window.draw(*lives[l]);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
		//                    GAME NOT OVER
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if (!game_over) {
			
			//Fuel Bar update
			current_fuel -= FUEL_LOSS_RATE; //Slowly goes down every frame
			fuelBar.setScale(current_fuel / 100, 1); //Scales green bar
			if (current_fuel <= 0) {
				current_fuel = 0; //prevent negative value

				if (!player.justDied) {
					player.justDied = true;
					death_position = player.get_position();

					player_lives--; //lost a life
					sf::RectangleShape* ptr = lives[0]; //pointer to 1st element
					delete(ptr); //deletes it & scooches the rest over
					lives.erase(lives.begin()); //deletes an actual life
					
				}

				if (player.justDied) {
					player.move_down(); //sinks the spaceship
				}

				//When spaceship sinks all the way to the bottom
				if (player.get_position().y >= WINDOW_HEIGHT - 60) {
					//Check if player still has lives for respawning
					if (player_lives > 0) {
						player.setPosition(death_position);
						current_fuel = 100;
						player.justDied = false;

					}
					else {
						//Player lost all lives
						game_over = true;
					}
				}
			}

			//Laser update
			for (int index = 0; index < lasers.size(); index++) {
				lasers[index]->move();
				if (lasers[index]->position.x > WINDOW_WIDTH) {
					//Delete instance of laser
					vector<Laser*>::iterator instance = lasers.begin();
					instance += index;
					delete(lasers[index]);
					lasers.erase(instance);
				}
			}

			//Bomb update
			for (int index = 0; index < bombs.size(); index++) {
				bombs[index]->move();
				if (bombs[index]->position.y > WINDOW_HEIGHT) {
					//Delete instance of bomb
					vector<Bomb*>::iterator instance = bombs.begin();
					instance += index;
					delete(bombs[index]);
					bombs.erase(instance);
				}
			}
		}
		else {
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
		//                   GAME OVER 
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if (player_position.y < WINDOW_HEIGHT) {
				player.move_down(); //Force player to sink
			}

		}
		
		//----------------[DRAWING]-----------------------//
	
		window.draw(score_text);
		window.draw(fuel_text);
		window.draw(greyBar);
		window.draw(fuelBar);
		
		if (!fuel_tank_destroyed) {
			window.draw(*fuelTank.get_shape());
		}
		window.draw(*saucer.get_shape());
		window.draw(*rocket.get_shape());

		window.draw(*player.get_shape());
		
		//Draw any laser instances in the lasers vector
		for (int i = 0; i < lasers.size(); i++) {
			window.draw(*(lasers[i]->getShape()));
		}

		//Draw any bomb instances in the bombs vector
		for (int j = 0; j < bombs.size(); j++) {
			window.draw(*(bombs[j]->getShape()));
		}

		window.display();
	}
	return 0;
}