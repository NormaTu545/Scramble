#pragma once
#include "AttackObject.h"
class Laser :
	public AttackObject {

public:
	Laser(sf::Vector2f spawnPos);
	void move();
};