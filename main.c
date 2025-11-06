// main.c

#include <stdlib.h>
#include <time.h>

#include "render.h"

// - identify the public functions provided by the library by inspecting the librenderer.dylib binary
//  - from their names, deduce their purpose and how they work together.
// - reverse-engineer the layout of the core data structure used by the library (likely a one C struct to operate on the window's state).

// Write a C program that uses the discovered API to:
// - correctly initialize the library, 
// - run its main loop,
// - and properly shut it down (if succeeded the an animation will appear in the window).

int main(void) {
    // You're allowed to modify this function as much as you want.
    // Please, provide a small description of what you have done and how.
    // And, try to avoid memory leaks :)

    // gfx_sleep(1000);
    
    gfx_context* ctx = malloc(sizeof(gfx_context));
    char* title = gfx_get_window_title();
    uint32_t width = gfx_get_width_screen();
    uint32_t height = gfx_get_height_screen();

    fprintf(stdout, "Window title: %s\n", title);
    fprintf(stdout, "Screen width: %d\n", width);
    fprintf(stdout, "Screen height: %d\n", height);

    gfx_create_context(ctx, width, height, title);

    fprintf(stdout, "Window title: %s\n", ctx->name);

    fprintf(stdout, "Screen height: %d\n", ctx->height);
    fprintf(stdout, "Screen width: %d\n", ctx->width);

    // gfx_init_context((void*)ctx);
    // gfx_context* ctx = gfx_create_context((void*)ctx, 1234, 800, 600);
    // gfx_get_window_title()   
    
    // ctx->name = gfx_get_window_title();
    // ctx->width = gfx_get_width_screen();
    // ctx->height = gfx_get_height_screen();
    // ctx->framebuffer = gfx_allocate_framebuffer(ctx);

    // gfx_loop((void*)ctx);
    // gfx_render((void*)ctx);
    // gfx_init_context((void*)ctx);

    // int gfxT = gfx_time();
    // struct timespec* tp = malloc(sizeof(struct timespec));
    // int my = clock_gettime(CLOCK_REALTIME, tp);
    // my = tp->tv_sec * 1000 + tp->tv_nsec / 1000000;
    
    // fprintf(stdout, "out gfx: %d ms\n", gfxT);
    // fprintf(stdout, "out our: %d ms\n", my);
    fprintf(stdout, "Ready to go?\n");

    free(ctx);
    // free(tp);
    return EXIT_SUCCESS;
}
