#include "Terrain.h"

Terrain::Terrain(int xSize_, int ySize_, int minHeight_, int snowHeight_)
        :
        xSize(xSize_),
        ySize(ySize_),
		minHeight(minHeight_),
		snowHeight(snowHeight_)
{

    for(int y = 0; y < ySize + 1; y++){
        for(int x = 0; x < xSize + 1; x++){
            terrainVertices.push_back({0, 0, 0});
        }
    }

    for(int y = 0; y < ySize; y++){
        for(int x = 0; x < xSize; x++){
			terrainTiles.push_back({0, 0, 0, x, y, terrainVertices[ y      * (xSize + 1) +  x     ].height,
                                                   terrainVertices[ y      * (xSize + 1) +  x + 1 ].height,
                                                   terrainVertices[(y + 1) * (xSize + 1) +  x     ].height,
                                                   terrainVertices[(y + 1) * (xSize + 1) + (x + 1)].height});
        }
    }

}

void Terrain::heightmap(const char* file_path) {
    SDL_Surface* temp = SDL_LoadBMP(file_path);
    unsigned char* pixels = (unsigned char*)temp->pixels;
    for(int y = 0; y < 65; y++){
        for(int x = 0; x < 65; x++){
            int r = pixels[3 * (y * temp->w + x) + 0];
            int g = pixels[3 * (y * temp->w + x) + 1];
            int b = pixels[3 * (y * temp->w + x) + 2];
            int avg = ((r + g + b) / 3) /4;
            terrainVertices[y * (xSize + 1) + x].height = avg;
        }
    }
}

void Terrain::randomPerlinHeight(int seed) {
    for(int y = 0; y < ySize + 1; y++){
        for(int x = 0; x < xSize + 1; x++){
            terrainVertices[y * (xSize + 1) + x].worldPosX = x; 
			terrainVertices[y * (xSize + 1) + x].worldPosY = y; 
			int pos = round(abs(scaled_octave_noise_2d(1, 1, 0.01, 0, 20, x, y)));
			if(pos < minHeight) {
				terrainVertices[y * (xSize + 1) + x].height = minHeight;
			}else{
				terrainVertices[y * (xSize + 1) + x].height = pos;
			}
        }
    }
}

void Terrain::loadSprites(const char* file_path, const char* file_path2, const char* file_path3, SDL_Renderer* renderer, int tileSize_) {
    SDL_Surface* temp = SDL_LoadBMP(file_path);
	SDL_SetColorKey(temp, SDL_TRUE, 0);
	sprite = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
	
	SDL_Surface* temp2 = SDL_LoadBMP(file_path2);
	SDL_SetColorKey(temp2, SDL_TRUE, 0);
	sprite2 = SDL_CreateTextureFromSurface(renderer, temp2);
	SDL_FreeSurface(temp2);
	
	SDL_Surface* temp3 = SDL_LoadBMP(file_path3);
	SDL_SetColorKey(temp3, SDL_TRUE, 0);
	sprite3 = SDL_CreateTextureFromSurface(renderer, temp3);
	SDL_FreeSurface(temp3);
	
	tileSize = tileSize_;
}

void Terrain::updateVertices(int camOffsetX, int camOffsetY, float scale) {
	convertedVertices.clear();
	for (int i = 0; i < terrainVertices.size(); i++) {
		int xPosition = terrainVertices[i].worldPosY * 64/scale;
		int yPosition = terrainVertices[i].worldPosY * 64/(scale*2);

		xPosition += terrainVertices[i].worldPosX * 64/scale;
		yPosition -= terrainVertices[i].worldPosX * 64/(scale*2);

		xPosition += camOffsetX;
		yPosition += camOffsetY;
		
		//xPosition -= std::abs((xPosition/scale));

        yPosition -= terrainVertices[i].height * ((tileSize/4)/scale) - (96/scale);
		
		terrainVertex temp = {xPosition, yPosition, terrainVertices[i].height};
		convertedVertices.push_back(temp);
	}
}

void Terrain::drawGrid(SDL_Renderer* renderer, int camOffsetX, int camOffsetY, float scale) {	
	SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
	for(int y = 0; y < ySize + 1; y++){
		SDL_Point* temporary;
		temporary = new SDL_Point[xSize+1];
        for(int x = 0; x < xSize + 1; x++) {
			SDL_Point tmp;
			tmp.x = convertedVertices[y * (xSize+1)+ x].worldPosX;
			tmp.y = convertedVertices[y * (xSize+1)+ x].worldPosY;
			temporary[x] = tmp;
		}
		SDL_RenderDrawLines(renderer, temporary, xSize+1);
		delete temporary;
	}
	for(int x = 0; x < xSize + 1; x++) {
		SDL_Point* temporary;
		temporary = new SDL_Point[ySize+1];
        for(int y = 0; y < ySize + 1; y++){
			SDL_Point tmp;
			tmp.x = convertedVertices[y * (xSize+1)+ x].worldPosX;
			tmp.y = convertedVertices[y * (xSize+1)+ x].worldPosY;
			temporary[y] = tmp;
		}
		SDL_RenderDrawLines(renderer, temporary, ySize+1);
		delete temporary;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Terrain::drawTerrain(SDL_Renderer* renderer, int camOffsetX, int camOffsetY, float scale) {
    for (int i = 0; i < terrainTiles.size(); i++) {
		int xPosition = terrainTiles[i].worldPosY * 64/scale;
		int yPosition = terrainTiles[i].worldPosY * 64/(scale*2);

		xPosition += terrainTiles[i].worldPosX * 64/scale;
		yPosition -= terrainTiles[i].worldPosX * 64/(scale*2);

		xPosition += camOffsetX;
		yPosition += camOffsetY;
		
		//xPosition += camOffsetX;

		//xPosition -= std::abs((xPosition/scale));

        //yPosition -= terrainTiles[i].baseHeight * ((tileSize/4)/scale);
		
		yPosition -= terrainTiles[i].baseHeight * ((tileSize/4)/scale);

		int sX, sY, eX, eY;

		sY = terrainTiles[i].typeY;
		sX = terrainTiles[i].typeX;

		sY *= tileSize;
		sX *= tileSize;

		eX = tileSize;
		eY = tileSize;

		if (xPosition > (-64 / (scale / 2)) && xPosition < (1280 + (64 / (scale / 2))) && yPosition >(-64 / (scale / 2)) && yPosition < (720 + (64 / (scale / 2)))) {
			SDL_Rect src = {sX, sY, eX, eY};
			SDL_Rect dest = {xPosition, yPosition, (int)(64/(scale / 2)), (int)(64/(scale / 2))};
			
			if(terrainTiles[i].baseHeight < minHeight + 1) {
				SDL_RenderCopyEx(renderer, sprite2, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
			}else if(terrainTiles[i].baseHeight > snowHeight || (terrainTiles[i].c1 > snowHeight || terrainTiles[i].c2 > snowHeight || terrainTiles[i].c3 > snowHeight || terrainTiles[i].c4 > snowHeight)) {
				SDL_RenderCopyEx(renderer, sprite3, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
			}else{
				SDL_RenderCopyEx(renderer, sprite, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
			}
	    }
    }
}

void Terrain::updateTiles() {
    for(auto& i : terrainTiles){
        i.baseHeight = std::min({i.c1, i.c2, i.c3, i.c4});
        int baseHeight = i.baseHeight;
        if(i.c1 == baseHeight     && i.c2 == baseHeight     && i.c3 == baseHeight     && i.c4 == baseHeight    ) { i.typeX = 0; i.typeY = 0; }
        if(i.c1 == baseHeight + 1 && i.c2 == baseHeight     && i.c3 == baseHeight     && i.c4 == baseHeight    ) { i.typeX = 1; i.typeY = 0; }
        if(i.c1 == baseHeight     && i.c2 == baseHeight     && i.c3 == baseHeight + 1 && i.c4 == baseHeight    ) { i.typeX = 2; i.typeY = 0; }
        if(i.c1 == baseHeight + 1 && i.c2 == baseHeight     && i.c3 == baseHeight + 1 && i.c4 == baseHeight    ) { i.typeX = 3; i.typeY = 0; }
        if(i.c1 == baseHeight     && i.c2 == baseHeight     && i.c3 == baseHeight     && i.c4 == baseHeight + 1) { i.typeX = 4; i.typeY = 0; }

        if(i.c1 == baseHeight + 1 && i.c2 == baseHeight     && i.c3 == baseHeight     && i.c4 == baseHeight + 1) { i.typeX = 0; i.typeY = 1; }
        if(i.c1 == baseHeight     && i.c2 == baseHeight     && i.c3 == baseHeight + 1 && i.c4 == baseHeight + 1) { i.typeX = 1; i.typeY = 1; }
        if(i.c1 == baseHeight + 1 && i.c2 == baseHeight     && i.c3 == baseHeight + 1 && i.c4 == baseHeight + 1) { i.typeX = 2; i.typeY = 1; }
        if(i.c1 == baseHeight     && i.c2 == baseHeight + 1 && i.c3 == baseHeight     && i.c4 == baseHeight    ) { i.typeX = 3; i.typeY = 1; }
        if(i.c1 == baseHeight + 1 && i.c2 == baseHeight + 1 && i.c3 == baseHeight     && i.c4 == baseHeight    ) { i.typeX = 4; i.typeY = 1; }

        if(i.c1 == baseHeight     && i.c2 == baseHeight + 1 && i.c3 == baseHeight + 1 && i.c4 == baseHeight    ) { i.typeX = 0; i.typeY = 2; }
        if(i.c1 == baseHeight + 1 && i.c2 == baseHeight + 1 && i.c3 == baseHeight + 1 && i.c4 == baseHeight    ) { i.typeX = 1; i.typeY = 2; }
        if(i.c1 == baseHeight     && i.c2 == baseHeight + 1 && i.c3 == baseHeight     && i.c4 == baseHeight + 1) { i.typeX = 2; i.typeY = 2; }
        if(i.c1 == baseHeight + 1 && i.c2 == baseHeight + 1 && i.c3 == baseHeight     && i.c4 == baseHeight + 1) { i.typeX = 3; i.typeY = 2; }
        if(i.c1 == baseHeight     && i.c2 == baseHeight + 1 && i.c3 == baseHeight + 1 && i.c4 == baseHeight + 1) { i.typeX = 4; i.typeY = 2; }

        if(i.c1 == baseHeight + 1 && i.c2 == baseHeight     && i.c3 == baseHeight + 2 && i.c4 == baseHeight + 1) { i.typeX = 0; i.typeY = 3; }
        if(i.c1 == baseHeight + 2 && i.c2 == baseHeight + 1 && i.c3 == baseHeight + 1 && i.c4 == baseHeight    ) { i.typeX = 1; i.typeY = 3; }
        if(i.c1 == baseHeight + 1 && i.c2 == baseHeight + 2 && i.c3 == baseHeight     && i.c4 == baseHeight + 1) { i.typeX = 2; i.typeY = 3; }
        if(i.c1 == baseHeight     && i.c2 == baseHeight + 1 && i.c3 == baseHeight + 1 && i.c4 == baseHeight + 2) { i.typeX = 3; i.typeY = 3; }
    }
}
