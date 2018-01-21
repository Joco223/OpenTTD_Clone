#pragma once

#include <string>
#include <SDL.h>
#include <iostream>

class Object {
public:
	SDL_Texture* sprite;
	SDL_Texture* sprite2;
	int worldPosX;
	int worldPosY;
	bool selected;

	Object(int, int);

	void loadSprite(const char*, SDL_Renderer*);
	void drawObject(int, int, float, SDL_Renderer*, SDL_Texture*);
	void checkIfSelected(int, int, int, int, float, SDL_Texture*);
};