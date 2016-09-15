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
    void toggle_scrolling_done(); //returns opposite of scroll_done

	//Heights of each individual chunk, manually coded
	float yPositions[TOTAL_BLOCKS] = {
		50, //0
		55, //1
		75, //2
		100,//3
		150,//4
		110,//5
		85, //6
		10, //7
		20, //8 
		60, //9
		80, //10
		400,//11
		10, //12
		50, //13
		75, //14
		20, //15 
		300, //16 
		400, //17
		400,//18
		400 //19
	};
};