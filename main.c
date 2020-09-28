
/**
 * 
 * This is a simple program to demonstrate how to use NoobSDL.h
 * 
 * Will write random noise to the screen.
 * 
 */


#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "NoobSDL.h"

// Setting values for the screen size, and resolution
static int WINDOW_WIDTH = 512;
static int WINDOW_HEIGHT = 512;

static int HORIZONTAL_RESOLUTION = 128;
static int VERTICAL_RESOLUTION = 128;




int main (void) {
	
	// This is to make random a bit more random.
	srand((unsigned)time(NULL));
	
	// This function initilizes SDL, and the window
	if (init_NoobSDL()) {
		// if init has an error, exit program.
		return 1;
	}
	
	
	short int loop = 1;
	
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
				
				// Get a random color, this can be replaced with a function to return a color based on a x and y value, or other
				SDL_Color rtn = (SDL_Color){rand()%255,rand()%255,rand()%255,255};

				// These statements write the RGBA values to the PIX_BUF array, which is written to the screen later
				int z = (y * PITCH + x * 4);
				PIX_BUF[z++] = rtn.a;
				PIX_BUF[z++] = rtn.r;
				PIX_BUF[z++] = rtn.g;
				PIX_BUF[z++] = rtn.b;
				
				/* 
				 * Pitch is the the Horizontal resolution * number of bytes per pixel (in this case, 4)
				 * The pixel data is one after the other, so z is set to the first position, then incremented along
				 * The pixel data is ordered Alpha, Red, Green, Blue
				 */
				
			}
		}
		
		
		// Draw PIX_BUF to screen
		render_NoobSDL();
		
	}
	
	
	// Exit function, cleans up SDL data, and pointers made with NoobSDL
	exit_NoobSDL();
	return 0;
}