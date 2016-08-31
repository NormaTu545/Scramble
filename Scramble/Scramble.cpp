// Scramble.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Player.h"
#include "Laser.h"
#include "Bomb.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500

using namespace std;

int main() {
	
	vector<Laser*> lasers;
	vector<Bomb*> bombs;
	bool game_over = false;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Scramble_Game");
	
	//--[Loading Game Stuff]-----------------------------------------------------------------

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

	//[Actual Game Loop]--------------------------------------------------

	while (window.isOpen())
	{
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			//Fires a laser & adds that instance to lasers vector
			if (player.fireRateTimer >= 5) { //Every 50 frames. 5/0.1 = 50
				sf::FloatRect currPos = player.get_position();
				sf::Vector2f ship_right_side(currPos.left + SHIP_WIDTH, currPos.top + SHIP_HEIGHT/2);

				Laser* pew = new Laser(ship_right_side); //Spawn laser at right of image
				//Add to list of lasers
				lasers.push_back(pew);
				player.fireRateTimer = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			//Drops a bomb & adds that instance to bombs vector 
			if (player.fireRateTimer >= 5) { //Every 50 frames. 5/0.1 = 50
				sf::FloatRect currPos = player.get_position();
				sf::Vector2f ship_bottom_side(currPos.left + SHIP_WIDTH/2, currPos.top + SHIP_HEIGHT);

				Bomb* boom = new Bomb(ship_bottom_side); //Spawn laser at bottom of image
			    //Adds this instance to list of bombs
				bombs.push_back(boom);
				player.fireRateTimer = 0; //resets timer
			}
		}

		//~~~~~~~~~~~~~~~~~~~~~~~[UPDATE]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		
		window.clear();

		if (!game_over) {
			player.update();

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
		
		//----------------[DRAWING]-----------------------//
		window.draw(background);

		window.draw(*player.get_shape());
		
		//Draw any laser instances in the lasers vector
		for (int i = 0; i < lasers.size(); i++) {
			window.draw(*(lasers[i]->getShape()));
		}

		//Draw any bomb instances in the bombs vector
		for (int j = 0; j < bombs.size(); j++) {
			window.draw(*(bombs[j]->getShape()));
		}
		//------------------------------------------------//
		window.display();
	}

	return 0;
}