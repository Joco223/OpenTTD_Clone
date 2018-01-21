#include "ObjectGroup.h"

ObjectGroup::ObjectGroup()
	:
	Sprite(nullptr),
	BorderSprite(nullptr),
	SelectedSprite(nullptr)
	{}

void ObjectGroup::loadSprite(const char* file_path, SDL_Renderer* renderer) {
	SDL_Surface* temp = SDL_LoadBMP(file_path);
	Sprite = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
}

void ObjectGroup::loadBorderSprite(const char* file_path, SDL_Renderer* renderer) {
	SDL_Surface* temp = SDL_LoadBMP(file_path);
	BorderSprite = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
}

void ObjectGroup::loadSelectedSprite(const char* file_path, SDL_Renderer* renderer) {
	SDL_Surface* temp = SDL_LoadBMP(file_path);
	SelectedSprite = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
}

void ObjectGroup::drawSpriteS(int camOffsetX, int camOffsetY, float scale, SDL_Renderer* renderer) {
	for (int i = 0; i < objects.size(); i++) {
		int tile_width, tile_height;
		SDL_QueryTexture(Sprite, nullptr, nullptr, &tile_width, &tile_height);

		int xPosition = objects[i].worldPosX * tile_width/scale;
		int yPosition = objects[i].worldPosX * tile_height/(scale*2);

		xPosition += objects[i].worldPosY * tile_width/scale;
		yPosition -= objects[i].worldPosY * tile_height/(scale*2);

		xPosition += camOffsetX;
		yPosition += camOffsetY;

		if (xPosition > (-128 / (scale / 2)) && xPosition < (1280 + (128 / (scale / 2))) && yPosition >(-128 / (scale / 2)) && yPosition < (720 + (128 / (scale / 2)))) {
			SDL_Rect src = {0, 0, tile_width, tile_height};
			SDL_Rect dest = {xPosition, yPosition, tile_width/(scale / 2), tile_height/(scale / 2)};

			SDL_RenderCopyEx(renderer, Sprite, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
		}
	}
}

void ObjectGroup::drawBorderSpriteS(int camOffsetX, int camOffsetY, float scale, SDL_Renderer* renderer) {
	for (int i = 0; i < objects.size(); i++) {
		int tile_width, tile_height;
		SDL_QueryTexture(BorderSprite, nullptr, nullptr, &tile_width, &tile_height);

		int xPosition = objects[i].worldPosX * tile_width/scale;
		int yPosition = objects[i].worldPosX * tile_height/(scale*2);

		xPosition += objects[i].worldPosY * tile_width/scale;
		yPosition -= objects[i].worldPosY * tile_height/(scale*2);

		xPosition += camOffsetX;
		yPosition += camOffsetY;

		if (xPosition > (-128 / (scale / 2)) && xPosition < (1280 + (128 / (scale / 2))) && yPosition >(-128 / (scale / 2)) && yPosition < (720 + (128 / (scale / 2)))) {
			SDL_Rect src = {0, 0, tile_width, tile_height};
			SDL_Rect dest = {xPosition, yPosition, tile_width/(scale / 2), tile_height/(scale / 2)};

			SDL_RenderCopyEx(renderer, BorderSprite, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
		}
	}
}

void ObjectGroup::drawSelectedSpriteS(int camOffsetX, int camOffsetY, float scale, SDL_Renderer* renderer) {
	for (int i = 0; i < objects.size(); i++) {
		int tile_width, tile_height;
		SDL_QueryTexture(SelectedSprite, nullptr, nullptr, &tile_width, &tile_height);

		int xPosition = objects[i].worldPosX * tile_width/scale;
		int yPosition = objects[i].worldPosX * tile_height/(scale*2);

		xPosition += objects[i].worldPosY * tile_width/scale;
		yPosition -= objects[i].worldPosY * tile_height/(scale*2);

		xPosition += camOffsetX;
		yPosition += camOffsetY;

		if (xPosition > (-128 / (scale / 2)) && xPosition < (1280 + (128 / (scale / 2))) && yPosition >(-128 / (scale / 2)) && yPosition < (720 + (128 / (scale / 2)))) {
			SDL_Rect src = {0, 0, tile_width, tile_height};
			SDL_Rect dest = {xPosition, yPosition, tile_width/(scale / 2), tile_height/(scale / 2)};

			SDL_RenderCopyEx(renderer, SelectedSprite, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
		}
	}
}