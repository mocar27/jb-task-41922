// render.h

#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>

#define EXIT_SUCCESS 0

// Work in progress

// some struct to operate on the window's state
// struct timespec* is used really often as well

// gfx_allocate_framebuffer
// gfx_close
// gfx_create_context
// gfx_init_context
// gfx_loop
// gfx_render

// Almost 
// void gfx_sleep(long nanoseconds); -- function creating two timespec* and calling nanosleep
// int gfx_time(void); -- it calls for clock_gettime and do some math operations on it, then returns int

// Success
int gfx_get_height_screen(void);
int gfx_get_width_screen(void);
char* gfx_get_window_title(void);

#endif // RENDER_H

// not public so we ignore
// void CGRectMake(void);
// internal_should_close
// internal_draw_rect

// non-public functions to draw stuff on the screen
// draw_text
// draw_char