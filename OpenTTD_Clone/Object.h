#pragma once

#include <string>
#include <SDL.h>
#include <iostream>

class Object {
public:
	SDL_Texture* sprite;
	int worldPosX;
	int worldPosY;
	int type;
	float height;

	Object(int, int, int, float);

	void drawObject(int, int, float, SDL_Renderer*);
};