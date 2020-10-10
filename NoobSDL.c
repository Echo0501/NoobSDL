/* NoodSDL.c */

#include <SDL2/SDL.h>
#include "NoobSDL.h"



SDL_Window * MAIN_WINDOW;
SDL_Renderer * MAIN_RENDERER;

SDL_Texture * TEXTURE_BUFFER;



int init_NoobSDL(int window_width, int window_height, int horizontal_resolution, int vertical_resolution) {
	
	WINDOW_WIDTH = window_width;
	WINDOW_HEIGHT = window_height;
	
	HORIZONTAL_RESOLUTION = horizontal_resolution;
	VERTICAL_RESOLUTION = vertical_resolution;
	
	
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL INIT ERR: %s\n", SDL_GetError());
		
		return 1;
	}
	
	
	// Create main_window
	MAIN_WINDOW = SDL_CreateWindow("NoobSDL Window",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					WINDOW_WIDTH,
					WINDOW_HEIGHT,
					0);

	// If failed to create window
	if (!MAIN_WINDOW) {
		printf("SDL CREATE WINDOW ERR: %s\n", SDL_GetError());
		SDL_Quit();
		
		return 1;
	}

	
	// Create renderer
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	MAIN_RENDERER = SDL_CreateRenderer(MAIN_WINDOW, -1, render_flags);

	// if failed to create renderer
	if (!MAIN_RENDERER) {
		printf("SDL CREATE RENDERER ERR: %s\n", SDL_GetError());
		SDL_DestroyWindow(MAIN_WINDOW);
		SDL_Quit();
	
		return 1;
	}
	
	
	// create SDL texture
	TEXTURE_BUFFER = SDL_CreateTexture(MAIN_RENDERER, 
								SDL_PIXELFORMAT_BGRA8888,
								SDL_TEXTUREACCESS_STREAMING,
								HORIZONTAL_RESOLUTION,
							  	VERTICAL_RESOLUTION);
	
	
	// create buffer to hold pixel data.
	PITCH = HORIZONTAL_RESOLUTION * 4;
	PIX_BUF = (unsigned char *) malloc(VERTICAL_RESOLUTION * PITCH);
	
	return 0;
}



void render_NoobSDL() {
	
	// Write Data to Texture
	SDL_UpdateTexture(TEXTURE_BUFFER, NULL, PIX_BUF, PITCH);
	
	// write texture to the screen
	SDL_RenderCopy(MAIN_RENDERER, TEXTURE_BUFFER, NULL, NULL);
	
	// update screen
	SDL_RenderPresent(MAIN_RENDERER);
	
}



void exit_NoobSDL() {
	// Cleanup and Exit
	free(PIX_BUF);
	SDL_DestroyTexture(TEXTURE_BUFFER);
	SDL_DestroyRenderer(MAIN_RENDERER);
	SDL_DestroyWindow(MAIN_WINDOW);
	SDL_Quit();
}