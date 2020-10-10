
/**
 * 
 * This is a simple program to demonstrate how to use NoobSDL.h
 * 
 */


#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "NoobSDL.h"



int main (void) {
	
	// This is to make random a bit more random.
	srand((unsigned)time(NULL));
	
	
	
	// This function initilizes SDL, and the window
	if (init_NoobSDL(512, 512, 128, 128)) {
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
		
		
		
		int z = 0;
		// Drawing to PIX_BUF
		for (int y = 0; y < VERTICAL_RESOLUTION; y++) {
			for (int x = 0; x < HORIZONTAL_RESOLUTION; x++) {
				
				int l = 255 * y / VERTICAL_RESOLUTION;
				
				// These statements write the RGBA values to the PIX_BUF array, which is written to the screen later
				PIX_BUF[z++] = 255; // ALPHA
				PIX_BUF[z++] = l; // RED
				PIX_BUF[z++] = l; // GREEN
				PIX_BUF[z++] = l; // BLUE
				
			}
		}
		
		
		
		// Draw PIX_BUF to screen
		render_NoobSDL();
	}
	
	
	
	// Exit function, cleans up SDL data, and pointers made with NoobSDL
	exit_NoobSDL();
	return 0;
}
