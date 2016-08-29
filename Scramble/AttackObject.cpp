#include "stdafx.h"
#include "AttackObject.h"

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// [BASE CLASS] Creates instance, has method move() to be overriden.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AttackObject::AttackObject() {
	//CREATE OBJECT, START POSITION, IMAGE, MOVE DIRECTION, REMOVE INSTANCE

	//Generic Rectangle shape
	//Texture will be overridden by subclasses
}


void AttackObject::destroy() {
	delete(this);
}

void AttackObject::move() {

}
//subclass LASER & BOMB as AttackObjects

