/* NoodSDL.c */

#include <SDL2/SDL.h>
#include "NoobSDL.h"


uint8_t * PIX_BUF;
size_t PITCH;

size_t WINDOW_WIDTH;
size_t WINDOW_HEIGHT;

size_t HORIZONTAL_RESOLUTION;
size_t VERTICAL_RESOLUTION;

SDL_Window * MAIN_WINDOW;
SDL_Renderer * MAIN_RENDERER;

SDL_Texture * TEXTURE_BUFFER;





/** Getter Functions **/

size_t get_window_width() {
	return WINDOW_WIDTH;
}

size_t get_window_height() {
	return WINDOW_HEIGHT;
}

size_t get_horizontal_resolution() {
	return HORIZONTAL_RESOLUTION;
}

size_t get_vertical_resolution() {
	return VERTICAL_RESOLUTION;
}



/** Private helpers **/






/** Init and Quit Functions **/

int init_NoobSDL(const size_t window_width, const size_t window_height, 
				 const size_t horizontal_resolution, const size_t vertical_resolution,
				 const char *Title) {
	
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
	MAIN_WINDOW = SDL_CreateWindow(Title,
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
	PITCH = HORIZONTAL_RESOLUTION << 2;
	PIX_BUF = (uint8_t *) malloc(VERTICAL_RESOLUTION * PITCH);
	
	return 0;
}


void quit_NoobSDL() {
	// Cleanup and Exit
	free(PIX_BUF);
	SDL_DestroyTexture(TEXTURE_BUFFER);
	SDL_DestroyRenderer(MAIN_RENDERER);
	SDL_DestroyWindow(MAIN_WINDOW);
	SDL_Quit();
}





/** Render and Draw functions **/

void render_NoobSDL() {
	
	// Write Data to Texture
	SDL_UpdateTexture(TEXTURE_BUFFER, NULL, PIX_BUF, PITCH);
	
	// write texture to the screen
	SDL_RenderCopy(MAIN_RENDERER, TEXTURE_BUFFER, NULL, NULL);
	
	// update screen
	SDL_RenderPresent(MAIN_RENDERER);
	
}

void draw_pixel(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	size_t z = (PITCH * y) + (x << 2);
	PIX_BUF[z++] = a; // ALPHA
	PIX_BUF[z++] = r; // RED
	PIX_BUF[z++] = g; // GREEN
	PIX_BUF[z++] = b; // BLUE
	
}

void clear_screen(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	size_t z = 0;
	while(z < PITCH * VERTICAL_RESOLUTION) {
		PIX_BUF[z++] = a; // ALPHA
		PIX_BUF[z++] = r; // RED
		PIX_BUF[z++] = g; // GREEN
		PIX_BUF[z++] = b; // BLUE
	}
}


