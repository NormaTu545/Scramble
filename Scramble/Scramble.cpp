// Scramble.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Player.h"
#include "Laser.h"
#include "Bomb.h"
#include "FuelTank.h"
#include "Saucer.h"
#include "Rocket.h"
#include "Terrain.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
#define FUEL_BAR_XPOS 635
#define FUEL_LOSS_RATE 0.005f
#define MAX_LIVES 3
using namespace std;

int main() {
	/* Declaring global variables */
	vector<Laser*> lasers;
	vector<Bomb*> bombs;
	bool game_over = false;
	bool fuel_tank_destroyed = false;
	bool saucer_destroyed = false;
	bool rocket_destroyed = false;
	bool rocket_flying = false;
	float current_fuel = 100; //Start 100% Full
	int player_lives = MAX_LIVES; //Start with 3 lives
	int score = 0;
	sf::Vector2f death_position;  //Save point where player died

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Scramble_Game");
	
	//--[Loading Game Stuff]-----------------------------------------------------------------

	// [Heads Up Display set up]
	sf::Text score_text;
	sf::Text fuel_text;
	sf::Text end_text;

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

	end_text.setFont(font);
	end_text.setCharacterSize(30);
	end_text.setPosition(WINDOW_WIDTH / 10, WINDOW_HEIGHT / 3);
	end_text.setColor(sf::Color::White);
	end_text.setString("GAME OVER!  PRESS -SPACE- TO PLAY AGAIN");

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

	for (int total_lives = 0; total_lives < MAX_LIVES; total_lives++) {
		sf::RectangleShape* player_life_img = new sf::RectangleShape(sf::Vector2f(50.0f, 40.0f));
		player_life_img->setTexture(&playerIMG);
		lives.push_back(player_life_img);
	}

	/* Make a player */
	Player player(WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2);

	/* Make a TEST Fuel Tank, Saucer, & Rocket */
	FuelTank fuelTank(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
	Saucer saucer(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 100);
	Rocket rocket(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT - 100);

	/* Make the horizontally scrolling terrain */
	Terrain* ground = new Terrain();

	vector<sf::RectangleShape*> terrainBlocks;
	terrainBlocks = ground->terrain;

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

	//[Actual Game Loop]--------------------------------------------------

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			/* Pressing SPACE restarts the game completely */
			if (game_over) {
				game_over = false;
				
				// Return player position & starting values to where they started
				player.setPosition(sf::Vector2f(WINDOW_WIDTH / 8, WINDOW_HEIGHT / 2));
				score = 0;
				current_fuel = 100;
				player_lives = MAX_LIVES;

				//Re-position game objects
				fuel_tank_destroyed = false;
				saucer_destroyed = false;
				rocket_destroyed = false;
				
				fuelTank.come_back(sf::Vector2f(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 3));
				saucer.come_back(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4));
				rocket.come_back(sf::Vector2f(WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT / 3));
				
				//Restock on lives
				for (int total_lives = 0; total_lives < MAX_LIVES; total_lives++) {
					sf::RectangleShape* player_life_img = new sf::RectangleShape(sf::Vector2f(50.0f, 40.0f));
					player_life_img->setTexture(&playerIMG);
					lives.push_back(player_life_img);
				}
			}
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
		[GAME EVENT HANDLING]
		*********************************************************************
		*/

		/* HANDLE ROCKET FLYING UP WHEN PLAYER IS W/IN VIEW OF ROCKET */

		if (rocket.get_position().left - player.get_position().x <= TRIGGER_DISTANCE) {
			rocket_flying = true;
		}

		if (rocket_flying) {
			rocket.fly_up();

			if (rocket.get_position().top <= 0) {
				rocket.go_away();
			}
		}

		/* HANDLE PLAYER GETTING HIT BY ANY OF THE GAME OBJECTS */
		/* (Game object is removed when player collides with it) */
		bool player_hit_fuel_tank = player.get_shape()->getGlobalBounds().intersects(fuelTank.get_position());
		bool player_hit_saucer = player.get_shape()->getGlobalBounds().intersects(saucer.get_position());
		bool player_hit_rocket = player.get_shape()->getGlobalBounds().intersects(rocket.get_position());

		if (player_hit_fuel_tank) {
			current_fuel = 0; //make player lose a life & empty the fuel bar
			fuelTank.go_away();
			fuel_tank_destroyed = true;
		}
		if (player_hit_saucer) {
			current_fuel = 0;
			saucer.go_away();
			saucer_destroyed = true;
		}
		if (player_hit_rocket) {
			current_fuel = 0;
			rocket.go_away();
			rocket_destroyed = true;
		}

		/* HANDLE LASER DESTROYING GAME OBJECTS */

		for (int i = 0; i < lasers.size(); i++) {
			bool hit_fuel_tank = (*lasers[i]).laser_shape.getGlobalBounds().intersects(fuelTank.get_position());
			bool hit_saucer = (*lasers[i]).laser_shape.getGlobalBounds().intersects(saucer.get_position());
			bool hit_rocket = (*lasers[i]).laser_shape.getGlobalBounds().intersects(rocket.get_position());

			if (hit_fuel_tank) {
				current_fuel += FUEL_AMOUNT;
				score += FUEL_SCORE_REWARD;
				fuelTank.go_away();

				delete(lasers[i]); //laser instance is now null ptr
				lasers.erase(lasers.begin() + i); //deletes null ptr
				fuel_tank_destroyed = true;
			}

			if (hit_saucer) {
				score += SAUCER_SCORE_REWARD;
				saucer.go_away();

				delete(lasers[i]); //laser instance is now null ptr
				lasers.erase(lasers.begin() + i); //deletes null ptr
				saucer_destroyed = true;
			}

			if (hit_rocket) {
				if (!rocket_flying) {
					score += ROCKET_SCORE_REWARD;
				}
				else {
					score += FLYING_ROCKET_SCORE_REWARD;
				}

				rocket.go_away();

				delete(lasers[i]); //laser instance is now null ptr
				lasers.erase(lasers.begin() + i); //deletes null ptr
				rocket_destroyed = true;
			}
		}

		/* HANDLE BOMB DESTROYING GAME OBJECTS */

		for (int j = 0; j < bombs.size(); j++) {
			bool hit_fuel_tank = (*bombs[j]).bomb_shape.getGlobalBounds().intersects(fuelTank.get_position());
			bool hit_saucer = (*bombs[j]).bomb_shape.getGlobalBounds().intersects(saucer.get_position());
			bool hit_rocket = (*bombs[j]).bomb_shape.getGlobalBounds().intersects(rocket.get_position());

			if (hit_fuel_tank) {
				current_fuel += FUEL_AMOUNT;
				score += FUEL_SCORE_REWARD;
				fuelTank.go_away();

				delete(bombs[j]); //bomb instance is now null ptr
				bombs.erase(bombs.begin() + j); //deletes null ptr
				fuel_tank_destroyed = true;
			}

			if (hit_saucer) {
				score += SAUCER_SCORE_REWARD;
				saucer.go_away();

				delete(bombs[j]); //laser instance is now null ptr
				bombs.erase(bombs.begin() + j); //deletes null ptr
				saucer_destroyed = true;
			}

			if (hit_rocket) {
				if (!rocket_flying) {
					score += ROCKET_SCORE_REWARD;
				}
				else {
					score += FLYING_ROCKET_SCORE_REWARD;
				}

				rocket.go_away();

				delete(bombs[j]); //laser instance is now null ptr
				bombs.erase(bombs.begin() + j); //deletes null ptr
				rocket_destroyed = true;
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
		//                   GAME OVER 
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if (game_over) {
			if (player.get_position().y < WINDOW_HEIGHT) {
				player.move_down(); //Force player to sink
			}
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
		//                    GAME NOT OVER
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		else {
			//Scrolling Terrain update
			ground->move();

			//Fuel Bar update
			current_fuel -= FUEL_LOSS_RATE; //Slowly goes down every frame
			fuelBar.setScale(current_fuel / 100, 1); //Scales green bar

			if (current_fuel >= 100) {
				current_fuel = 100; //prevent fuel going past 100%
			}
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
					player.justDied = false;
					if (player_lives > 0) {
						player.setPosition(death_position);
						current_fuel = 100;

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
			//		} //End of ORIGINAL game not over check

			//----------------[DRAWING]-----------------------//

			window.draw(score_text);
			window.draw(fuel_text);
			window.draw(greyBar);
			window.draw(fuelBar);

			if (game_over)
				window.draw(end_text);

			if (!fuel_tank_destroyed) 
				window.draw(*fuelTank.get_shape());
			
			if (!saucer_destroyed) 
				window.draw(*saucer.get_shape());
			
			if (!rocket_destroyed) 
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

			//Draw the blocks of the horizontally scrolling terrain
			for (int k = 0; k < terrainBlocks.size(); k++) {
				window.draw(*terrainBlocks[k]);
			}

			window.display();
		}
	} //game not over closing bracket
	return 0;
}