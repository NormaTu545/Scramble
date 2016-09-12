#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain() {
	sf::Vector2f sizeVect(150, 500);
	sf::Vector2f spawnPos(0, WINDOW_HEIGHT); //bottom left corner
	
    //--Set up ground texture IMG loading--//
	if (!ground_image.loadFromFile("ground.jpg")) {
		cout << "Couldn't load ground.jpg!" << endl;
	}

	//The level is 30 chunks long
	for (int i = 0; i < 30; i++) {
		sf::RectangleShape* shape = new sf::RectangleShape(sizeVect);
		shape->setTexture(&ground_image);
		shape->setPosition(sf::Vector2f(spawnPos.x, spawnPos.y - positions[i]));
		spawnPos.x += sizeVect.x;
		terrain.push_back(shape);
	}
}

void Terrain::move() {
	for (int i = 0; i < terrain.size(); i++) {

		if (terrain[terrain.size() - 1]->getPosition().x > WINDOW_WIDTH - 150) {
			sf::Vector2f dir(-1 * MOVE_SPEED, 0);
			terrain[i]->move(dir);
		}
	}
}