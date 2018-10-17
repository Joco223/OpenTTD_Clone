#pragma once

#include <vector>
#include <SDL.h>
#include <math.h>
#include <iostream>

#include "Object.h"

class ObjectGroup {
public:
	std::vector<Object> objects;
	SDL_Texture* Sprite;
	int spriteSize;

	ObjectGroup();

	void loadSprite(const char*, SDL_Renderer*, int);

	void drawSpriteS(int, int, float, SDL_Renderer*);
};
