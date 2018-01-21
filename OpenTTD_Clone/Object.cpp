#include "Object.h"

Object::Object(int xPos, int yPos)
	:
	worldPosX(xPos),
	worldPosY(yPos),
	selected(false)
	{}

void Object::loadSprite(const char* file_path, SDL_Renderer* renderer) {
	SDL_Surface* temp = SDL_LoadBMP("C:/Users/jovanipavle/Desktop/Grass8.bmp");
	sprite = SDL_CreateTextureFromSurface(renderer, temp);

	SDL_FreeSurface(temp);
}

void Object::drawObject(int camOffsetX, int camOffsetY, float scale, SDL_Renderer* renderer, SDL_Texture* objSprite) {
	int tile_width, tile_height;
	SDL_QueryTexture(objSprite, nullptr, nullptr, &tile_width, &tile_height);

	int xPosition = worldPosX * tile_width/scale;
	int yPosition = worldPosX * tile_height/(scale*2);

	xPosition += worldPosY * tile_width/scale;
	yPosition -= worldPosY * tile_height/(scale*2);

	xPosition += camOffsetX;
	yPosition += camOffsetY;

	if (xPosition > (-128 / (scale / 2)) && xPosition < (1280 + (128 / (scale / 2))) && yPosition >(-128 / (scale / 2)) && yPosition < (720 + (128 / (scale / 2)))) {
		SDL_Rect src = {0, 0, tile_width, tile_height};
		SDL_Rect dest = {xPosition, yPosition, tile_width/(scale / 2), tile_height/(scale / 2)};

		SDL_RenderCopyEx(renderer, objSprite, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
	}
}

void Object::checkIfSelected(int mouseX, int mouseY, int camOffsetX, int camOffsetY, float scale, SDL_Texture* objSprite) {
	int tile_width, tile_height;
	SDL_QueryTexture(objSprite, nullptr, nullptr, &tile_width, &tile_height);

	int xPosition = worldPosX * tile_width/scale;
	int yPosition = worldPosX * tile_height/(scale * 2);

	xPosition += worldPosY * tile_width/scale;
	yPosition -= worldPosY * tile_height/(scale * 2);

	xPosition += camOffsetX;
	yPosition += camOffsetY;

	if (mouseX > xPosition && mouseX < xPosition + 2*(tile_width / scale) && mouseY > yPosition + (tile_height / scale) && mouseY < yPosition + 2*(tile_height / scale)) {
		selected = !selected;
	}
}