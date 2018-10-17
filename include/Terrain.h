#pragma once

#include <vector>
#include <SDL.h>
#include <math.h>
#include <random>
#include <algorithm>
#include <iostream>

#include "Object.h"
#include "ObjectGroup.h"
#include "Simplex.h"

class Terrain{
private:
    int xSize, ySize, minHeight, snowHeight; 
    SDL_Texture* sprite;
	SDL_Texture* sprite2;
	SDL_Texture* sprite3;
    //SDL_Texture* combinedSprite;
    int tileSize;
    int combinedSize;

    struct terrainTile {
        int baseHeight;
        int typeX;
        int typeY;
        int worldPosX;
    	int worldPosY;
        int& c1;
        int& c2;
        int& c3;
        int& c4;
    };
	
	struct terrainVertex {
		int worldPosX;
		int worldPosY;
		int height;
	};

    bool cmpY (terrainTile i, terrainTile j) { return (i.worldPosY < j.worldPosY); }
    bool cmpX (terrainTile i, terrainTile j) { return (i.worldPosX < j.worldPosX); }
    bool cmpH (terrainTile i, terrainTile j) { return (i.baseHeight > j.baseHeight); }

    std::vector<terrainTile> terrainTiles;
	std::vector<terrainVertex> terrainVertices;
	std::vector<terrainVertex> convertedVertices;

public:
    Terrain(int, int, int, int);

    void randomPerlinHeight(int);
    void heightmap(const char*);
    void loadSprites(const char*, const char*, const char*, SDL_Renderer*, int);
    void updateTiles();
    void drawTerrain(SDL_Renderer*, int, int, float);
	void drawGrid(SDL_Renderer*, int, int, float);
	void updateVertices(int, int, float);
};
