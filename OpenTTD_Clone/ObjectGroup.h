#pragma once

#include <vector>
#include <SDL.h>

#include "Object.h"

class ObjectGroup {
public:
	std::vector<Object> objects;
	SDL_Texture* Sprite;
	SDL_Texture* BorderSprite;
	SDL_Texture* SelectedSprite;

	ObjectGroup();

	void loadSprite(const char*, SDL_Renderer*);
	void loadBorderSprite(const char*, SDL_Renderer*);
	void loadSelectedSprite(const char*, SDL_Renderer*);

	void drawSpriteS(int, int, float, SDL_Renderer*);
	void drawBorderSpriteS(int, int, float, SDL_Renderer*);
	void drawSelectedSpriteS(int, int, float, SDL_Renderer*);
};