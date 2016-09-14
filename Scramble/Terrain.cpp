#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain() {
	sf::Vector2f sizeVect(150, 500);
	sf::Vector2f spawnPos(0, WINDOW_HEIGHT); //bottom left corner
	deltaX = 0;

    //--Set up ground texture IMG loading--//
	if (!ground_image.loadFromFile("ground.jpg")) {
		cout << "Couldn't load ground.jpg!" << endl;
	}

	//The scrolling level is 20 blocks long
	for (int i = 0; i < TOTAL_BLOCKS; i++) {
		sf::RectangleShape* shape = new sf::RectangleShape(sizeVect);
		shape->setTexture(&ground_image);
		shape->setPosition(sf::Vector2f(spawnPos.x, spawnPos.y - yPositions[i]));
		xPositions.push_back(spawnPos.x + sizeVect.x / 2);
		spawnPos.x += sizeVect.x;
		terrain.push_back(shape);
	}
}

void Terrain::move() {
	for (int i = 0; i < terrain.size(); i++) {
		//Move blocks left while the 20 blocks are still onscreen
		if (terrain[terrain.size() - 1]->getPosition().x > WINDOW_WIDTH - 150) {
			sf::Vector2f dir(-1 * MOVE_SPEED, 0);
			terrain[i]->move(dir);
		}
		else {
			scroll_done = true;
		}
		
	}
	deltaX += MOVE_SPEED;
}

void Terrain::reset() {
	sf::Vector2f* delta = new sf::Vector2f(deltaX, 0);
	for (int i = 0; i < terrain.size(); i++) {
		terrain[i]->move(*delta);
	}
	deltaX = 0;
}

bool Terrain::scrolling_done() {
	return scroll_done;
}