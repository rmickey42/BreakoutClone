#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <stdio.h>
#include <vector>
#include "gameboard.h"

#define printsdlerr(s) fprintf(stderr, "%s SDL_Error: %s\n", s, SDL_GetError());

const char* IMAGE_PATHS[] = {"../images/1.bmp"};
const int IMAGE_COUNT = 1;
std::vector<SDL_Surface*> g_images;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* g_window = NULL;
SDL_Surface* g_screen = NULL;

int loadImage(const char* path){
	int curIm = g_images.size();
	SDL_Surface* image = SDL_LoadBMP(path);
    if(image == NULL){
        printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
        return -1;
    }
	g_images.push_back(image);
	return curIm;
}

void free_images() {
	for(int i = 0; i < g_images.size(); i++){
		SDL_FreeSurface(g_images[i]);
	}
}

bool loadAllImages(){
	bool allLoaded = true;
	for(int i = 0; i < IMAGE_COUNT; i++){
		if(loadImage(IMAGE_PATHS[i]) == -1){
			allLoaded = false;
		}
	}
	return allLoaded;
}

int gameloop(){
	SDL_Event e; 
	bool quit = false; 

	while(!quit){ 
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
    	}
	}
}

int main(int argc, char* argv[]){
	g_images = std::vector<SDL_Surface*>();

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printsdlerr("SDL could not initialize.");
		return EXIT_FAILURE;
	}

	g_window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(g_window == NULL){
		printsdlerr("Window could not be created.");
		return EXIT_FAILURE;
	}
	
	g_screen = SDL_GetWindowSurface(g_window);

	int retval = gameloop();

	SDL_DestroyWindow(g_window);
	SDL_Quit();
	free_images();

	return retval;
}
