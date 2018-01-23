#include <SDL.h>
#include <iostream>
#include <vector>
#include <algorithm> 

#include "ObjectGroup.h"
#include "Object.h"
#include "TrainEngine.h"

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
bool cmpH (Object i,Object j) { return (i.height > j.height); }

int main(int argc, char* argv[]) {
	window = SDL_CreateWindow("OpenTTD Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Event event;

	ObjectGroup grass;
	ObjectGroup rails;

	TrainEngine engine1(2.2, 3, 2.2, 1, 0);

	engine1.loadSprites("C:/Users/jovanipavle/Desktop/OpenTTD Clone Resources/Sprites/Engines/Test/Test.bmp", renderer);

	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			Object tmp(x, y, 0, 0);
			grass.objects.push_back(tmp);		
		}
	}

	/*Object tmp(3, 3, 0, 1);
	grass.objects.push_back(tmp);

	Object tmp2(2, 3, 6, 0.5);
	grass.objects.push_back(tmp2);

	Object tmp3(2, 2, 5, 0.5);
	grass.objects.push_back(tmp3);

	Object tmp4(3, 2, 4, 0.5);
	grass.objects.push_back(tmp4);

	Object tmp5(3, 4, 8, 0.5);
	grass.objects.push_back(tmp5);

	Object tmp6(4, 3, 2, 0.5);
	grass.objects.push_back(tmp6);

	Object tmp7(4, 2, 3, 0.5);
	grass.objects.push_back(tmp7);

	Object tmp8(4, 4, 1, 0.5);
	grass.objects.push_back(tmp8);

	Object tmp9(2, 4, 7, 0.5);
	grass.objects.push_back(tmp9);*/

	Object t1(2, 3, 0, 0);
	Object t2(1, 3, 2, 0);
	Object t3(1, 2, 1, 0);
	Object t4(3, 1, 5, 0);
	Object t5(3, 3, 3, 0);
	Object t6(2, 1, 0, 0);
	Object t7(1, 1, 4, 0);
	Object t8(3, 2, 1, 0);
	Object t9(1, 1, 0, 0);
	Object t10(0, 1, 0, 0);

	rails.objects.push_back(t1);
	rails.objects.push_back(t2);
	rails.objects.push_back(t3);
	rails.objects.push_back(t4);
	rails.objects.push_back(t5);
	rails.objects.push_back(t6);
	rails.objects.push_back(t7);
	rails.objects.push_back(t8);
	rails.objects.push_back(t9);
	rails.objects.push_back(t10);

	rails.loadSprite("C:/Users/jovanipavle/Desktop/OpenTTD Clone Resources/Sprites/Rails/Normal/BMP/Rails.bmp", renderer);
	grass.loadSprite("C:/Users/jovanipavle/Desktop/OpenTTD Clone Resources/Sprites/Base/BMP/Base.bmp", renderer);


	int cooldown = 0;
	float scale = 2;

	bool space = false;

	/*std::sort(grass.objects.begin(), grass.objects.end(), cmpH);

	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			int t, tr, r, br, b, bl, l, tl;
			if (y == 4 && x == 4) {
				if(grass.objects[y * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {tl = 1;}
				if(grass.objects[(y - 1) * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {l = 1;}
				if(grass.objects[(y - 1) * 5 + x].height < grass.objects[y * 5 + x].height) {bl = 1;}
			}else if (y == 0 && x == 4) {
				if(grass.objects[y * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {tl = 1;}
				if(grass.objects[(y + 1) * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {t = 1;}
				if(grass.objects[(y + 1) * 5 + x].height < grass.objects[y * 5 + x].height) {tr = 1;}
			}else if (y == 0 && x == 0) {
				if(grass.objects[(y + 1) * 5 + x].height < grass.objects[y * 5 + x].height) {tr = 1;}
				if(grass.objects[(y + 1) * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {r = 1;}
				if(grass.objects[y * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {br = 1;}
			}else if (y == 4 && x == 0) {
				if(grass.objects[y * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {br = 1;}
				if(grass.objects[(y - 1) * 5 + x].height < grass.objects[y * 5 + x].height) {bl = 1;}
				if(grass.objects[(y - 1) * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {b = 1;}
			}else if (x == 0) {
				if(grass.objects[(y + 1) * 5 + x].height < grass.objects[y * 5 + x].height) {tr = 1;}
				if(grass.objects[(y + 1) * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {r = 1;}
				if(grass.objects[y * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {br = 1;}
				if(grass.objects[(y - 1) * 5 + x].height < grass.objects[y * 5 + x].height) {bl = 1;}
				if(grass.objects[(y - 1) * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {b = 1;}
			}else if (x == 4) {
				if(grass.objects[(y + 1) * 5 + x].height < grass.objects[y * 5 + x].height) {tr = 1;}
				if(grass.objects[(y + 1) * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {t = 1;}
				if(grass.objects[y * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {tr = 1;}
				if(grass.objects[(y - 1) * 5 + x].height < grass.objects[y * 5 + x].height) {bl = 1;}
				if(grass.objects[(y - 1) * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {l = 1;}
			}else if (y == 0) {
				if(grass.objects[y * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {tl = 1;}
				if(grass.objects[(y + 1) * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {t = 1;}
				if(grass.objects[(y + 1) * 5 + x].height < grass.objects[y * 5 + x].height) {tr = 1;}
				if(grass.objects[(y + 1) * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {r = 1;}
				if(grass.objects[y * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {br = 1;}
			}else if (y == 4) {
				if(grass.objects[y * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {tl = 1;}
				if(grass.objects[(y - 1) * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {l = 1;}
				if(grass.objects[y * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {br = 1;}
				if(grass.objects[(y - 1) * 5 + x].height < grass.objects[y * 5 + x].height) {bl = 1;}
				if(grass.objects[(y - 1) * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {b = 1;}
			}else {
				if(grass.objects[(y + 1) * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {t = 1;}
				if(grass.objects[(y + 1) * 5 + x].height < grass.objects[y * 5 + x].height) {tr = 1;}
				if(grass.objects[(y + 1) * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {r = 1;}
				if(grass.objects[y * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {tl = 1;}
				if(grass.objects[(y - 1) * 5 + (x - 1)].height < grass.objects[y * 5 + x].height) {l = 1;}
				if(grass.objects[y * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {br = 1;}
				if(grass.objects[(y - 1) * 5 + x].height < grass.objects[y * 5 + x].height) {bl = 1;}
				if(grass.objects[(y - 1) * 5 + (x + 1)].height < grass.objects[y * 5 + x].height) {b = 1;}
			}

			if(t == 1) {grass.objects[(y + 1) * 5 + (x - 1)].type == 7; }
			if(tr == 1) {grass.objects[(y + 1) * 5 + (x - 1)].type == 8; }
			if(r == 1) {grass.objects[(y + 1) * 5 + (x - 1)].type == 1; }
			if(tl == 1) {grass.objects[(y + 1) * 5 + (x - 1)].type == 6; }
			if(l == 1) {grass.objects[(y + 1) * 5 + (x - 1)].type == 5; }
			if(br == 1) {grass.objects[(y + 1) * 5 + (x - 1)].type == 2; }
			if(bl == 1) {grass.objects[(y + 1) * 5 + (x - 1)].type == 4; }
			if(b == 1) {grass.objects[(y + 1) * 5 + (x - 1)].type == 3; }
		}
	}*/

	std::sort(grass.objects.begin(), grass.objects.end(), cmpY);
	std::sort(grass.objects.begin(), grass.objects.end(), cmpX);
	std::sort(grass.objects.begin(), grass.objects.end(), cmpH);
	std::reverse(grass.objects.begin(), grass.objects.end());

	std::sort(rails.objects.begin(), rails.objects.end(), cmpY);
	std::sort(rails.objects.begin(), rails.objects.end(), cmpX);
	std::reverse(rails.objects.begin(), rails.objects.end());

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
		if (scale > 32) {
			scale = 32;
		}

		cooldown++;

		SDL_RenderClear(renderer);

		grass.drawSpriteS(camXPos, camYPos, scale, renderer);
		rails.drawSpriteS(camXPos, camYPos, scale, renderer);

		if(space == true) {
			engine1.updateEngine(rails.objects);
		}
		engine1.drawEngine(camXPos, camYPos, scale, renderer);
		
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}

