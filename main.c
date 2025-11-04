// main.c

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

    hello_world();
    fprintf(stdout, "Ready to go?\n");
    return EXIT_SUCCESS;
}
