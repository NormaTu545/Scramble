#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 1000
#define MOVE_SPEED 0.2f
#define TOTAL_BLOCKS 20

using namespace std;

class Terrain {

private:
	sf::Texture ground_image;
	bool scroll_done = false;

public:
	Terrain(); //Constructor

	// The terrain is a collection of rectangleshape chunks
	vector<sf::RectangleShape*> terrain;
	vector<float> xPositions;
	float deltaX;

	void move(); //chunks move left at a constant speed
	void reset(); //for restarting the scrolling terrain over again 
	bool scrolling_done(); //returns T/F if terrain is still scrolling
    void set_scrolling_done(bool value); //returns opposite of scroll_done

	//Heights of each individual chunk, manually coded
	float yPositions[TOTAL_BLOCKS] = {
		50,  //0
		75,  //1
		100, //2
		75,  //3
		200, //4 saucer_1 here
		250, //5
		100, //6
		25,  //7 rocket_1 here
		40,  //8 
		100, //9 fuel_tank_1 here
		250, //10 saucer_2 here
		300, //11
		100, //12 rocket_2 here
		90,  //13 fuel_tank_2 here
		75,  //14
		20,  //15 
		100, //16 
		200, //17
		250, //18
		250  //19
	};
};