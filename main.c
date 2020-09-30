
/**
 * 
 * This is a simple program to demonstrate how to use NoobSDL.h
 * 
 * Will write random noise to the screen.
 *
 * Compiled on linux with 'gcc -ggdb3 -Wall -O3 -o main main.c `sdl2-config --cflags --libs`'
 *
 */


#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "NoobSDL.h"



int main (void) {
	
	// This is to make random a bit more random.
	srand((unsigned)time(NULL));
	
	// Setting values for the screen size, and resolution
	WINDOW_WIDTH = 512;
	WINDOW_HEIGHT = 512;

	HORIZONTAL_RESOLUTION = 128;
	VERTICAL_RESOLUTION = 128;
	
	
	
	// This function initilizes SDL, and the window
	if (init_NoobSDL()) {
		// if init has an error, exit program.
		return 1;
	}
	
	unsigned short int loop = 1;
	
	
	// Main loop
	while(loop) {
		
		// Basic Event Handling
		SDL_Event evt;
		while (SDL_PollEvent(&evt)) {
			switch (evt.type) {
				case SDL_QUIT:
					loop = 0;
					break;
				default:
					break;
			}
		}
		
		
		// Drawing to PIX_BUF
		for (int y = 0; y < VERTICAL_RESOLUTION; y++) {
			for (int x = 0; x < HORIZONTAL_RESOLUTION; x++) {
				
				SDL_Color rtn;
				
				// Get a random color, this can be replaced with a function to return a color based on a x and y value, or other
				rtn = (SDL_Color){rand()%255,rand()%255,rand()%255,255};
				
				// These statements write the RGBA values to the PIX_BUF array, which is written to the screen later
				int z = (y * PITCH + x * 4);
				PIX_BUF[z++] = rtn.a;
				PIX_BUF[z++] = rtn.r;
				PIX_BUF[z++] = rtn.g;
				PIX_BUF[z++] = rtn.b;
				
			}
		}
		
		// Draw PIX_BUF to screen
		render_NoobSDL();
	}
	
	
	// Exit function, cleans up SDL data, and pointers made with NoobSDL
	exit_NoobSDL();
	return 0;
}
