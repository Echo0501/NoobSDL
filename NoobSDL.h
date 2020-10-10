/**
 * 
 * 
 * 
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