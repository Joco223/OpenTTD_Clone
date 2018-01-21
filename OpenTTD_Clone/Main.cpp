#include <SDL.h>
#include <iostream>
#include <vector>
#include <algorithm> 

#include "ObjectGroup.h"
#include "Object.h"

SDL_Window* window;
SDL_Surface* surface;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Surface* pixelSpace;
SDL_Surface* pixelSpace2;
unsigned int* pixels;
unsigned int* pixels2;

bool quit;

float camXPos = 0;
float camYPos = 0;

bool w = false;
bool a = false;
bool s = false;
bool d = false;
bool q = false;
bool e = false;
bool click = false;

constexpr int WIDTH = 1280, HEIGHT = 720;

bool cmpY (Object i,Object j) { return (i.worldPosY < j.worldPosY); }
bool cmpX (Object i,Object j) { return (i.worldPosX > j.worldPosX); }

int main(int argc, char* argv[]) {
	window = SDL_CreateWindow("OpenTTD Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Event event;

	ObjectGroup grass;
	ObjectGroup grassU;
	ObjectGroup grassT;
	ObjectGroup grassTR;
	ObjectGroup grassR;
	ObjectGroup grassBR;
	ObjectGroup grassB;
	ObjectGroup grassBL;
	ObjectGroup grassL;
	ObjectGroup grassTL;

	grass.loadSprite("C:/Users/jovanipavle/Desktop/Grass.bmp", renderer);
	grassU.loadSprite("C:/Users/jovanipavle/Desktop/GrassU.bmp", renderer);
	grassT.loadSprite("C:/Users/jovanipavle/Desktop/GrassT.bmp", renderer);
	grassTR.loadSprite("C:/Users/jovanipavle/Desktop/GrassRT.bmp", renderer);
	grassR.loadSprite("C:/Users/jovanipavle/Desktop/GrassR.bmp", renderer);
	grassBR.loadSprite("C:/Users/jovanipavle/Desktop/GrassBR.bmp", renderer);
	grassB.loadSprite("C:/Users/jovanipavle/Desktop/GrassB.bmp", renderer);
	grassBL.loadSprite("C:/Users/jovanipavle/Desktop/GrassBL.bmp", renderer);
	grassL.loadSprite("C:/Users/jovanipavle/Desktop/GrassL.bmp", renderer);
	grassTL.loadSprite("C:/Users/jovanipavle/Desktop/GrassLT.bmp", renderer);

	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			Object tmp(x, y);
			grass.objects.push_back(tmp);
		}
	}

	int cooldown = 0;
	float scale = 2;

	std::sort(grass.objects.begin(), grass.objects.end(), cmpY);

	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN: {
				click = true;
				break; }
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_w:
						w = true;
						break;
					case SDLK_s:
						s = true;
						break;
					case SDLK_a:
						a = true;
						break;
					case SDLK_d:
						d = true;
						break;
					case SDLK_q:
						q = true;
						break;
					case SDLK_e:
						e = true;
						break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
					case SDLK_w:
						w = false;
						break;
					case SDLK_s:
						s = false;
						break;
					case SDLK_a:
						a = false;
						break;
					case SDLK_d:
						d = false;
						break;
					case SDLK_q:
						q = false;
						break;
					case SDLK_e:
						e = false;
						break;
				}
			break;
			}
			
		}

		float speed = 6;

		if (click == true) {
			int mouseX = event.motion.x;
			int mouseY = event.motion.y;

			/*for (int i = 0; i < groundTiles.objects.size(); i++) {
				//groundTiles.objects[i].checkIfSelected(mouseX, mouseY, camXPos, camYPos, scale, groundTiles.Sprite);
			}*/

			click = false;
		}

		if (w == true) {
			camYPos += speed;
		}
		if (s == true) {
			camYPos -= speed;
		}
		if (a == true) {
			camXPos += speed;
		}
		if (d == true) {
			camXPos -= speed;
		}
		if (q == true && cooldown > 10) {
			scale *= 2;
			cooldown = 0;
		}
		if (e == true && cooldown > 10) {
			scale /= 2;
			cooldown = 0;
		}
		if (scale < 0.5) {
			scale = 0.5;
		}
		if (scale > 16) {
			scale = 16;
		}

		cooldown++;

		SDL_RenderClear(renderer);

		grass.drawSpriteS(camXPos, camYPos, scale, renderer);
		/*grassU.drawSpriteS(camXPos, camYPos, scale, renderer);
		grassT.drawSpriteS(camXPos, camYPos, scale, renderer);
		grassTR.drawSpriteS(camXPos, camYPos, scale, renderer);
		grassR.drawSpriteS(camXPos, camYPos, scale, renderer);
		grassBR.drawSpriteS(camXPos, camYPos, scale, renderer);
		grassB.drawSpriteS(camXPos, camYPos, scale, renderer);
		grassBL.drawSpriteS(camXPos, camYPos, scale, renderer);
		grassL.drawSpriteS(camXPos, camYPos, scale, renderer);
		grassTL.drawSpriteS(camXPos, camYPos, scale, renderer);*/
		
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}

