/**
 * Header file for NoobSDL
 * 
 * Call init with sizes.
 * Write pixels with draw_pixel
 * then call render_NoobSDL()
 * 
 */

#ifndef NOOBSDL
#define NOOBSDL


size_t get_window_width();
size_t get_window_height();
size_t get_horizontal_resolution();
size_t get_vertical_resolution();

int init_NoobSDL(const size_t window_width, const size_t window_height, 
				 const size_t horizontal_resolution, const size_t vertical_resolution,
				 const char *Title);
void quit_NoobSDL();

void clear_screen(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_pixel(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void render_NoobSDL();


#endif