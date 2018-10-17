#include "ObjectGroup.h"

ObjectGroup::ObjectGroup()
	:
	Sprite(nullptr)
	{}

void ObjectGroup::loadSprite(const char* file_path, SDL_Renderer* renderer, int spriteSize_) {
	SDL_Surface* temp = SDL_LoadBMP(file_path);
	SDL_SetColorKey(temp, SDL_TRUE, 0x000000);
	Sprite = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
	for (int i = 0; i < objects.size(); i++) {
		objects[i].sprite = Sprite;
	}
	spriteSize = spriteSize_;
}

void ObjectGroup::drawSpriteS(int camOffsetX, int camOffsetY, float scale, SDL_Renderer* renderer) {
	for (int i = 0; i < objects.size(); i++) {
		int tile_width, tile_height;
		SDL_QueryTexture(Sprite, nullptr, nullptr, &tile_width, &tile_height);

		int xPosition = objects[i].worldPosX * 64/scale;
		int yPosition = objects[i].worldPosX * 64/(scale*2);

		xPosition += objects[i].worldPosY * 64/scale;
		yPosition -= objects[i].worldPosY * 64/(scale*2);

		xPosition += camOffsetX;
		yPosition += camOffsetY;

		int sX, sY, eX, eY;

		sY = (floor(objects[i].type / 5));
		sX = (objects[i].type - (sY * 5));

		sY *= 64;
		sX *= 64;

		eX = spriteSize;
		eY = spriteSize;

		if (xPosition > (-64 / (scale / 2)) && xPosition < (1280 + (64 / (scale / 2))) && yPosition >(-64 / (scale / 2)) && yPosition < (720 + (64 / (scale / 2)))) {
			SDL_Rect src = {sX, sY, eX, eY};
			SDL_Rect dest = {xPosition, yPosition, (int)(64/(scale / 2)), (int)(64/(scale / 2))};

			SDL_RenderCopyEx(renderer, Sprite, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
		}
	}
}
