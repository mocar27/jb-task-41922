// main.c

#include "render.h"

// - identify the public functions provided by the library by inspecting the librenderer.dylib binary
//  - from their names, deduce their purpose and how they work together.
// - reverse-engineer the layout of the core data structure used by the library (likely a one C struct to operate on the window's state).

// Write a C program that uses the discovered API to:
// - correctly initialize the library, 
// - run its main loop,
// - and properly shut it down (if succeeded the an animation will appear in the window).

// arguments are passed in following order of registers
// rdi, rsi, rdx, rcx, r8, r9
// of function is stored in rax

// 7th and next are Passed on the stack in reverse order, so the last argument is the first one pushed onto the stack.
// Floating-point arguments: Passed in separate floating-point registers (%xmm0 through %xmm7). 

int main(void) {
    // You're allowed to modify this function as much as you want.
    // Please, provide a small description of what you have done and how.
    // And, try to avoid memory leaks :)

    // gfx_sleep(999999999); // sleep for 1 second - holds really really long
    // int t = gfx_time();
    // fprintf(stdout, "Current time: %d\n", t);

    int x = gfx_get_height_screen();
    int y = gfx_get_width_screen();
    char* str = gfx_get_window_title();

    fprintf(stdout, "Window title: %s\n", str);

    fprintf(stdout, "Screen height: %d\n", x);
    fprintf(stdout, "Screen width: %d\n", y);
    fprintf(stdout, "Ready to go?\n");
    return EXIT_SUCCESS;
}
