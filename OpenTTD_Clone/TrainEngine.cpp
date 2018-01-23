#include "TrainEngine.h"

TrainEngine::TrainEngine(float xPos, float yPos, float speed_, int direction_, int height_) 
	:
	sprites(nullptr),
	worldPosX(xPos),
	worldPosY(yPos),
	prevXPos(xPos),
	prevYPos(yPos),
	speed(speed_),
	direction(direction_),
	type(direction_),
	height(height_)
	{}


void TrainEngine::loadSprites(const char* file_path, SDL_Renderer* renderer) {
	SDL_Surface* temp = SDL_LoadBMP(file_path);
	sprites = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
}

void TrainEngine::drawEngine(int camOffsetX, int camOffsetY, float scale, SDL_Renderer* renderer) {
	int tile_width, tile_height;
	SDL_QueryTexture(sprites, nullptr, nullptr, &tile_width, &tile_height);

	float xPosition = worldPosX * 128/scale;
	float yPosition = worldPosX * 128/(scale*2);

	xPosition += worldPosY * 128/scale;
	yPosition -= worldPosY * 128/(scale*2);

	xPosition += camOffsetX;
	yPosition += camOffsetY;

	yPosition -= (floor(height) * (56/(scale*2)));

	int sX, sY, eX, eY;

	switch (type) {
		case  0: sX =   0; sY =   0; eX = 128; eY = 128; break;
		case  1: sX = 128; sY =   0; eX = 128; eY = 128; break;
		case  2: sX = 256; sY =   0; eX = 128; eY = 128; break;
		case  3: sX = 384; sY =   0; eX = 128; eY = 128; break;
		case  4: sX =   0; sY = 128; eX = 128; eY = 128; xPosition += 64/scale; break;
		case  5: sX = 128; sY = 128; eX = 128; eY = 128; xPosition += 64/scale; break;
		case  6: sX = 256; sY = 128; eX = 128; eY = 128; xPosition -= 64/scale; break;
		case  7: sX = 384; sY = 128; eX = 128; eY = 128; xPosition -= 64/scale; break;
		case  8: sX =   0; sY = 256; eX = 128; eY = 128; yPosition -= 64/(scale*2); break;
		case  9: sX = 128; sY = 256; eX = 128; eY = 128; yPosition -= 64/(scale*2); break;
		case 10: sX = 256; sY = 256; eX = 128; eY = 128; yPosition += 64/(scale*2); break;
		case 11: sX = 384; sY = 256; eX = 128; eY = 128; yPosition += 64/(scale*2); break;
		case 12: sX =   0; sY = 384; eX = 128; eY = 128; yPosition += 64/(scale*2); break;
		case 13: sX = 128; sY = 384; eX = 128; eY = 128; break;
		case 14: sX = 256; sY = 384; eX = 128; eY = 128; break;
		case 15: sX = 384; sY = 384; eX = 128; eY = 128; break;
		case 16: sX =   0; sY = 512; eX = 128; eY = 128; break;
		case 17: sX = 128; sY = 512; eX = 128; eY = 128; break;
		case 18: sX = 256; sY = 512; eX = 128; eY = 128; break;
		case 19: sX = 384; sY = 512; eX = 128; eY = 128; break;
	}

	if (xPosition > (-128 / (scale / 2)) && xPosition < (1280 + (128 / (scale / 2))) && yPosition >(-128 / (scale / 2)) && yPosition < (720 + (128 / (scale / 2)))) {
		SDL_Rect src = {sX, sY, eX, eY};
		SDL_Rect dest = {xPosition, yPosition, 128/(scale / 2), 128/(scale / 2)};

		SDL_RenderCopyEx(renderer, sprites, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
	}
}

void TrainEngine::updateEngine(std::vector<Object>& rails) {
	int wX = round(worldPosX);
	int wY = round(worldPosY);

	for (int i = 0; i < rails.size(); i++) {
		if (rails[i].worldPosX == wX && rails[i].worldPosY == wY) {
			if(rails[i].type == 0) {if(prevXPos < rails[i].worldPosX) {type = 0; worldPosY = round(worldPosY);} else {if(prevXPos == rails[i].worldPosX) {type = type;} else {type = 1; worldPosY = round(worldPosY);} } }
			if(rails[i].type == 1) {if(prevYPos < rails[i].worldPosY) {type = 3; worldPosX = round(worldPosX); } else {if(prevYPos == rails[i].worldPosY) {type = type;} else {type = 2; worldPosX = round(worldPosX); } } }
			if(rails[i].type == 2) {if(prevYPos < rails[i].worldPosY) {type = 8;} else {if(prevXPos > rails[i].worldPosX) {type = 9;} else{ type = type; } } }
			if(rails[i].type == 3) {if(prevYPos < rails[i].worldPosY) {type = 4;} else {if(prevXPos < rails[i].worldPosX) {type = 5;} else{ type = type; } } }
			if(rails[i].type == 4) {if(prevYPos > rails[i].worldPosY) {type = 6;} else {if(prevXPos > rails[i].worldPosX) {type = 7;} else{ type = type; } } }
			if(rails[i].type == 5) {if(prevXPos < rails[i].worldPosX) {type = 10;} else {if(prevYPos > rails[i].worldPosY) {type = 11;} else{ type = type;  } } }
			if(rails[i].type == 6) {if(direction == 1) {type = 15;} else {type = 12;} }
			if(rails[i].type == 7) {if(direction == 1) {type = 14;} else {type = 13;} }
			if(rails[i].type == 8) {if(direction == 1) {type = 16;} else {type = 8;} }
			if(rails[i].type == 9) {if(direction == 1) {type = 17;} else {type = 19;} }
		}
	}

	if (wX != prevXPos) {
		prevXPos = wX;
	}
	if (wY != prevYPos) {
		prevYPos = wY;
	}

	if(type == 0) {worldPosX += 0.01 * speed;}
	if(type == 1) {worldPosX -= 0.01 * speed;}

	if(type == 3) {worldPosY += 0.01 * speed;}
	if(type == 2) {worldPosY -= 0.01 * speed;}

	if(type == 8) {worldPosX += 0.00707 * speed; worldPosY += 0.00707 * speed;}
	if(type == 9) {worldPosX -= 0.00707 * speed; worldPosY -= 0.00707 * speed;}

	if(type == 4) {worldPosX -= 0.00707 * speed; worldPosY += 0.00707 * speed;}
	if(type == 5) {worldPosX += 0.00707 * speed; worldPosY -= 0.00707 * speed;}

	if(type == 7) {worldPosX -= 0.00707 * speed; worldPosY += 0.00707 * speed;}
	if(type == 6) {worldPosX += 0.00707 * speed; worldPosY -= 0.00707 * speed;}

	if(type == 10) {worldPosX += 0.00707 * speed; worldPosY += 0.00707 * speed;}
	if(type == 11) {worldPosX -= 0.00707 * speed; worldPosY -= 0.00707 * speed;}
	

	if(type == 15) {worldPosX -= 0.007 * speed; worldPosY += 0.007 * speed;}
	if(type == 12) {worldPosX += 0.007 * speed; worldPosY -= 0.007 * speed;}
}