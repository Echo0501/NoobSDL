

/* Static Variables to be set in main program */
static int WINDOW_WIDTH;
static int WINDOW_HEIGHT;

static int HORIZONTAL_RESOLUTION;
static int VERTICAL_RESOLUTION;


#define DELTA_X (WINDOW_WIDTH / HORIZONTAL_RESOLUTION)
#define DELTA_Y (WINDOW_HEIGHT / VERTICAL_RESOLUTION)

/* This is a pointer to be used to write pixel data */
static unsigned char * PIX_BUF;

static int PIX_SIZE;
static int PITCH;

SDL_Window * MAIN_WINDOW;
SDL_Renderer * MAIN_RENDERER;


int init_NoobSDL() {
	
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL INIT ERR: %s\n", SDL_GetError());
		
		return 1;
	}

	
	
	// Create main_window
	MAIN_WINDOW = SDL_CreateWindow("Lich",
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
	
	// Allocate buffer for program to write pixel data to
	PIX_SIZE = VERTICAL_RESOLUTION * HORIZONTAL_RESOLUTION * 4;
	PIX_BUF = (unsigned char *) malloc(PIX_SIZE);
	
	return 0;
}

void render_NoobSDL() {
	
	// pointer to SDL texture pixel data
	unsigned char * pix;
	
	// create SDL texture
	SDL_Texture * BUFFER = SDL_CreateTexture(MAIN_RENDERER, 
								SDL_PIXELFORMAT_BGRA8888,
								SDL_TEXTUREACCESS_STREAMING,
								HORIZONTAL_RESOLUTION,
							  	VERTICAL_RESOLUTION);
	
	// Get pixel data, and prepare to write to texture
	SDL_LockTexture(BUFFER, NULL, (void**)&pix, &PITCH);
	
	// Write data from PIX_BUF to T\texture
	memcpy(pix,PIX_BUF,PIX_SIZE);
	
	// stop writing to texture
	SDL_UnlockTexture(BUFFER);
	
	// write texture to the screen
	SDL_RenderCopy(MAIN_RENDERER, BUFFER, NULL, NULL);
	
	// cleanup
	SDL_DestroyTexture(BUFFER);
	
	// update screen
	SDL_RenderPresent(MAIN_RENDERER);
}


int exit_NoobSDL() {
	// Cleanup and Exit
	SDL_DestroyRenderer(MAIN_RENDERER);
	SDL_DestroyWindow(MAIN_WINDOW);
	SDL_Quit();
	
	free(PIX_BUF);
	
	return 0;
}