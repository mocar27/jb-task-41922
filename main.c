// main.c

#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "render.h"

void *render_thread(void *ctx) {
    // Send render event to the window's queue,
    // that draws the content of the framebuffer to the window.
    gfx_render(ctx, 0);

    // Give the main loop a moment to receive the information
    gfx_sleep(5000);

    // At the end send close event to close the window gracefully.
    gfx_close(ctx);
    return NULL;
}

int main(void) {
    // You're allowed to modify this function as much as you want.
    // Please, provide a small description of what you have done and how.
    // And, try to avoid memory leaks :)

    // We stay careful with memory allocation, as at any time 
    // there might be an inside function failure, that we're not responsible for.

    // This main implementation is my idea my how main function should look like,
    // but as being unable to test it, as I mentioned in the README.md,
    // it really bumms me down.

    // Since gfx_create_context calls memset to fill the struct with 0s
    // and later stores it's arguments in the struct, we first need to have
    // allocated memory for it before calling gfx_create_context
    gfx_context* ctx = malloc(sizeof(gfx_context));
    if (!ctx) {
        fprintf(stderr, "Failed to allocate gfx_context\n");
        return EXIT_FAILURE;
    }

    // Retrieve arguments from hard-coded functions.
    uint64_t title_addr = gfx_get_window_title();
    int32_t width = gfx_get_width_screen();
    int32_t height = gfx_get_height_screen();

    // We call gfx_create_context to initialize the struct, set all the attributes to 0,
    // set values from arguments and allocate memory for the framebuffer.
    gfx_create_context(ctx, width, height, title_addr);

    // fprintf(stdout, "Created gfx_context with title at address: 0x%llx, width: %d, height: %d\n", ctx->name_addr, ctx->width,  ctx->height);
    
    ctx->framebuffer = gfx_allocate_framebuffer(ctx);
    if (!ctx->framebuffer) {
        fprintf(stderr, "Failed to allocate framebuffer\n");
        free(ctx);
        return EXIT_FAILURE;
    }
    
    // When all the initializations of context are done, we can initialize the graphics context.
    gfx_init_context(ctx);
    
    pthread_t thread;
    if (pthread_create(&thread, NULL, render_thread, ctx) != 0) {
        perror("pthread_create failed");
        return EXIT_FAILURE;
    }

    // In librender_x86_64.so, gfx_loop runs until receiving close event (event type 0).
    gfx_loop(ctx);

    // Gracefully wait for created thread and free allocated resources.
    pthread_join(thread, NULL);
    free(ctx->framebuffer);
    free(ctx);
    return EXIT_SUCCESS;
}
