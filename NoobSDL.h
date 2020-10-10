/**
 * Header file for NoobSDL
 * 
 * Call init with sizes.
 * Write data to PIX_BUF, then call render_NoobSDL.
 * Pitch is set to HORIZONTAL_RESOLUTION * (bytes per pixel)
 */


int WINDOW_WIDTH;
int WINDOW_HEIGHT;

int HORIZONTAL_RESOLUTION;
int VERTICAL_RESOLUTION;

unsigned char * PIX_BUF;
int PITCH;


int init_NoobSDL(int window_width, int window_height, int horizontal_resolution, int vertical_resolution);
void render_NoobSDL();
void exit_NoobSDL();