#pragma once

#include <SDL.h>
#include <vector>

#include "Object.h"

class TrainEngine {
public:
	SDL_Texture* sprites;
	float speed;
	float worldPosX;
	float worldPosY;
	int prevXPos;
	int prevYPos;
	float height;
	int type;
	int direction;

	TrainEngine(float, float, float, int, int);

	void loadSprites(const char* sprites_path, SDL_Renderer* renderer);
	void drawEngine(int camOffsetX, int camOffsetY, float scale, SDL_Renderer* renderer);
	void updateEngine(std::vector<Object>& rails);
};