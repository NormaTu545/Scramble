// Scramble.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include "Laser.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500

using namespace std;

int main() {
	
	vector<Laser*> lasers;
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
			//Fires a laser & adds that instance to draw list 
			if (player.fireRateTimer >= 5) {
				sf::FloatRect currPos = player.get_position();
				sf::Vector2f ship_right_side(currPos.left + SHIP_WIDTH, currPos.top);

				Laser* pew = new Laser(ship_right_side); //Spawn laser at right of image
				//Add to list of lasers
				lasers.push_back(pew);
				player.fireRateTimer = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {

			//image_draw_list.push_back(player.drop_bomb());
		}

		//~~~~~~~~~~~~~~~~~~~~~~~[UPDATE]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		
		window.clear();
		if (!game_over) {
			player.update();
			for (int index = 0; index < lasers.size(); index++) {
			
				lasers[index]->move();
				if (lasers[index]->position.x > WINDOW_WIDTH) {
					//Delete instance of laser
					vector<Laser*>::iterator k = lasers.begin();
					k += index;
					delete(lasers[index]);
					lasers.erase(k);
				}
				
			}
		}
		

		window.draw(background);
		window.draw(*player.get_shape());
		for (int i = 0; i < lasers.size(); i++) {
			window.draw(*(lasers[i]->getShape()));
		}
		//Draw all images mapped to a RecangleShape

		window.display();
	}

	return 0;
}