
/**
 * 
 * This is a simple program to demonstrate how to use NoobSDL.h
 * 
 */


#include <stdlib.h>
#include <SDL2/SDL.h>

#include "NoobSDL.h"



int main (void) {
	
	// This function initilizes SDL, and the window
	if (init_NoobSDL(512, 512, 128, 128, "Demo Window")) {
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
		for (int y = 0; y < get_vertical_resolution(); y++) {
			for (int x = 0; x < get_horizontal_resolution(); x++) {
				
				uint8_t l = 255 * (x + y * get_horizontal_resolution()) / (get_vertical_resolution() * get_horizontal_resolution());
				
				draw_pixel(x, y, l, l, l, 255);
				
			}
		}
		
		
		
		
		
		
		
		
		
		// Draw PIX_BUF to screen
		render_NoobSDL();
	}
	
	
	
	// Exit function, cleans up SDL data, and pointers made with NoobSDL
	quit_NoobSDL();
	return 0;
}
