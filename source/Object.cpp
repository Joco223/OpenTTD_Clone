#include "Object.h"

Object::Object(int xPos, int yPos, int type_, float height_)
	:
	worldPosX(xPos),
	worldPosY(yPos),
	type(type_),
	height(height_)
	{}


void Object::drawObject(int camOffsetX, int camOffsetY, float scale, SDL_Renderer* renderer) {
	
}
