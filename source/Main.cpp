#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "ObjectGroup.h"
#include "Object.h"
#include "Terrain.h"

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

int main(int argc, char* argv[]) {
	window = SDL_CreateWindow("OpenTrans", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	SDL_Event event;

	int cooldown = 0;
	int tileSize = 64;
	int terrainSize = 128;
	int minHeight = 4;
	int snowHeight = 14;
	float scale = 2;

	bool space = false;

	Terrain test(terrainSize, terrainSize, minHeight, snowHeight);

	test.loadSprites("assets/sprites/Base/Base32N.bmp", "assets/sprites/Base/Base32W.bmp", "assets/sprites/Base/Base32S.bmp", renderer, tileSize);
	//test.heightmap("assets/heightmaps/test2.bmp");
	test.randomPerlinHeight(54321);
	test.updateVertices(camXPos, camYPos, scale);
	test.updateTiles();
	//test.combineTerrain(renderer, scale);

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
					case SDLK_SPACE:
						space = !space;
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
		float newSpeed = speed;

		if (click == true) {
			int mouseX = event.motion.x;
			int mouseY = event.motion.y;

			/*for (int i = 0; i < groundTiles.objects.size(); i++) {
				//groundTiles.objects[i].checkIfSelected(mouseX, mouseY, camXPos, camYPos, scale, groundTiles.Sprite);
			}*/

			click = false;
		}

		if (w == true) {
			camYPos += newSpeed;
		}
		if (s == true) {
			camYPos -= newSpeed;
		}
		if (a == true) {
			camXPos += newSpeed;
		}
		if (d == true) {
			camXPos -= newSpeed;
		}
		if (q == true && cooldown > 10) {
			scale *= 2;
			newSpeed /= 2;
			cooldown = 0;
		}
		if (e == true && cooldown > 10) {
			scale /= 2;
			newSpeed *= 2;
			cooldown = 0;
		}
		if (scale < 0.5) {
			newSpeed /= 2;
			scale = 0.5;
		}
		if (scale > 128) {
			newSpeed *= 2;
			scale = 128;
		}

		cooldown++;

		SDL_RenderClear(renderer);

		test.updateVertices(camXPos, camYPos, scale);
		test.drawTerrain(renderer, camXPos, camYPos, scale);
		test.drawGrid(renderer, camXPos, camYPos, scale);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
