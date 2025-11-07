// main.c

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "render.h"

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

    // gfx_allocate_framebuffer
    // gfx_create_context
    // gfx_get_height_screen
    // gfx_get_width_screen
    // gfx_get_window_title
    // gfx_init_context

    // gfx_loop
    // gfx_render
    // gfx_time
    // gfx_sleep
    // gfx_close

    // Allocate memory for gfx_context
    // and create context

    gfx_context* ctx = malloc(sizeof(gfx_context));
    int64_t title = gfx_get_window_title();
    int32_t width = gfx_get_width_screen();
    int32_t height = gfx_get_height_screen();

    // fprintf(stderr, "Allocated gfx_context at: %p\n", (void*)title);

    fprintf(stdout, "Window title: %s\n", title);
    fprintf(stdout, "Screen width: %d\n", width);
    fprintf(stdout, "Screen height: %d\n", height);

    gfx_create_context(ctx, width, height, title);
    ctx->framebuffer = gfx_allocate_framebuffer(ctx);

    fprintf(stdout, "Window title: %s\n", ctx->name_addr);
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

    free(ctx->framebuffer);
    free(ctx);
    // free(tp);
    return EXIT_SUCCESS;
}
