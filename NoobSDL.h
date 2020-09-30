

/* Static Variables to be set in main program */
static int WINDOW_WIDTH;
static int WINDOW_HEIGHT;

static int HORIZONTAL_RESOLUTION;
static int VERTICAL_RESOLUTION;





SDL_Window * MAIN_WINDOW;
SDL_Renderer * MAIN_RENDERER;

static SDL_Texture * TEXTURE_BUFFER;

static unsigned char * PIX_BUF;
static int PITCH;

int init_NoobSDL() {
	
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
	
	// Get pixel data, and prepare to write to texture
	SDL_LockTexture(TEXTURE_BUFFER, NULL, (void**)&PIX_BUF, &PITCH);
	
	
	
	return 0;
}

void render_NoobSDL() {
	
	// stop writing to texture
	SDL_UnlockTexture(TEXTURE_BUFFER);
	
	// write texture to the screen
	SDL_RenderCopy(MAIN_RENDERER, TEXTURE_BUFFER, NULL, NULL);
	
	// update screen
	SDL_RenderPresent(MAIN_RENDERER);
	
	// Get pixel data, and prepare to write to texture
	SDL_LockTexture(TEXTURE_BUFFER, NULL, (void**)&PIX_BUF, &PITCH);
	
}


int exit_NoobSDL() {
	// Cleanup and Exit
	SDL_DestroyTexture(TEXTURE_BUFFER);
	SDL_DestroyRenderer(MAIN_RENDERER);
	SDL_DestroyWindow(MAIN_WINDOW);
	SDL_Quit();
	
	return 0;
}