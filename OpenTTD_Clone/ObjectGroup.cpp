#include "ObjectGroup.h"

ObjectGroup::ObjectGroup()
	:
	Sprite(nullptr)
	{}

void ObjectGroup::loadSprite(const char* file_path, SDL_Renderer* renderer) {
	SDL_Surface* temp = SDL_LoadBMP(file_path);
	Sprite = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
	for (int i = 0; i < objects.size(); i++) {
		objects[i].sprite = Sprite;
	}
}

void ObjectGroup::drawSpriteS(int camOffsetX, int camOffsetY, float scale, SDL_Renderer* renderer) {
	for (int i = 0; i < objects.size(); i++) {
		int tile_width, tile_height;
		SDL_QueryTexture(Sprite, nullptr, nullptr, &tile_width, &tile_height);

		int xPosition = objects[i].worldPosX * 128/scale;
		int yPosition = objects[i].worldPosX * 128/(scale*2);

		xPosition += objects[i].worldPosY * 128/scale;
		yPosition -= objects[i].worldPosY * 128/(scale*2);

		xPosition += camOffsetX;
		yPosition += camOffsetY;

		yPosition -= (floor(objects[i].height) * (56/(scale*2)));

		int sX, sY, eX, eY;

		switch (objects[i].type) {
			case  0: sX =   0; sY =   0; eX = 128; eY = 128; break;
			case  1: sX = 128; sY =   0; eX = 128; eY = 128; break;
			case  2: sX = 256; sY =   0; eX = 128; eY = 128; break;
			case  3: sX = 384; sY =   0; eX = 128; eY = 128; break;
			case  4: sX =   0; sY = 128; eX = 128; eY = 128; break;
			case  5: sX = 128; sY = 128; eX = 128; eY = 128; break;
			case  6: sX = 256; sY = 128; eX = 128; eY = 128; break;
			case  7: sX = 384; sY = 128; eX = 128; eY = 128; break;
			case  8: sX =   0; sY = 256; eX = 128; eY = 128; break;
			case  9: sX = 128; sY = 256; eX = 128; eY = 128; break;
			case 10: sX = 256; sY = 256; eX = 128; eY = 128; break;
			case 11: sX = 384; sY = 256; eX = 128; eY = 128; break;
			case 12: sX =   0; sY = 384; eX = 128; eY = 128; break;
			case 13: sX = 128; sY = 384; eX = 128; eY = 128; break;
			case 14: sX = 256; sY = 384; eX = 128; eY = 128; break;
			case 15: sX = 384; sY = 384; eX = 128; eY = 128; break;
		}

		if (xPosition > (-128 / (scale / 2)) && xPosition < (1280 + (128 / (scale / 2))) && yPosition >(-128 / (scale / 2)) && yPosition < (720 + (128 / (scale / 2)))) {
			SDL_Rect src = {sX, sY, eX, eY};
			SDL_Rect dest = {xPosition, yPosition, 128/(scale / 2), 128/(scale / 2)};

			SDL_RenderCopyEx(renderer, Sprite, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
		}
	}
}