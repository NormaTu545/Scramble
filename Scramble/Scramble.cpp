// Scramble.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500

using namespace std;

int main() {
	vector<sf::RectangleShape*> image_draw_list = *(new vector<sf::RectangleShape*>());

	bool game_over = false;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Scramble_Game");
	
	//[Loading Stuff]-------------------------------------------------------------------

	sf::Texture outer_space;

	if (!outer_space.loadFromFile("space.jpg")) {
		cout << "Couldn't load space.jpg!" << endl;
		return EXIT_FAILURE;
	}

	sf::Sprite background;
	background.setTexture(outer_space);
	
	/* Scale background manually to fit the window */
	background.setScale(1.6f, 1.5f);
	
	Player player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	image_draw_list.push_back(player.get_shape());
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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player.move_down();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player.move_left();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player.move_right();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			
			//image_draw_list.push_back(player.fire_laser());
		}


		//~~~~~~~~~~~~~~~~~~~~~~~[UPDATE]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		if (!game_over) {
			player.update();
		}


		window.clear();
		window.draw(background);
		//window.draw(player.get_shape());
		for (int i = 0; i < image_draw_list.size(); i++) {
			window.draw(*image_draw_list[i]);
		}

		window.display();
	}

	return 0;
}