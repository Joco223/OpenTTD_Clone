#pragma once

#include <vector>
#include <SDL.h>

#include "Object.h"

class ObjectGroup {
public:
	std::vector<Object> objects;
	SDL_Texture* Sprite;

	ObjectGroup();

	void loadSprite(const char*, SDL_Renderer*);

	void drawSpriteS(int, int, float, SDL_Renderer*);
};