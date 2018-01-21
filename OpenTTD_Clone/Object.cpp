#include "Object.h"

Object::Object(int xPos, int yPos, int type_, float height_)
	:
	worldPosX(xPos),
	worldPosY(yPos),
	type(type_),
	height(height_)
	{}


void Object::drawObject(int camOffsetX, int camOffsetY, float scale, SDL_Renderer* renderer) {
	int tile_width, tile_height;
	SDL_QueryTexture(sprite, nullptr, nullptr, &tile_width, &tile_height);

	int xPosition = worldPosX * tile_width/scale;
	int yPosition = worldPosX * tile_height/(scale*1.891);

	xPosition += worldPosY * tile_width/scale;
	yPosition -= worldPosY * tile_height/(scale*1.891);

	xPosition += camOffsetX;
	yPosition += camOffsetY;

	if (xPosition > (-128 / (scale / 2)) && xPosition < (1280 + (128 / (scale / 2))) && yPosition >(-128 / (scale / 1.891)) && yPosition < (720 + (128 / (scale / 1.891)))) {
		SDL_Rect src = {0, 0, tile_width, tile_height};
		SDL_Rect dest = {xPosition, yPosition, tile_width/(scale / 2), tile_height/(scale / 1.891)};

		SDL_RenderCopyEx(renderer, sprite, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
	}
}
