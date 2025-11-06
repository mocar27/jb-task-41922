// render.h

#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>

/** 
 * Arguments to functions are passed in following order of registers
 * rdi, rsi, rdx, rcx, r8, r9
 * Result of function is stored in rax or if pointer was passed,
 * then it is saved in respective pointer from input arguments.
 * (*) 7th and next are Passed on the stack in reverse order,
 * so the last argument is the first one pushed onto the stack.
 * Float arguments are passed in separate floating-point registers (%xmm{..}).

 * Ints are 32 bits registers - eax, ebx, ecx, edx, esi, edi.
 * Longs/pointers are 64 bits - rax, rbx, rcx, rdx, rsi, rdi.
 */

// gfx_context has size of 1072 and it makes sense, since in gfx_close there is a call to address stored in this struct
// with the offset of 1064 (428h in gfx_close reference), this value is assigned in gfx_init_context function
typedef struct gfx_context {
    uint64_t name;                  // in the offset 0 (from init_context read of addresses, holds the name casted to uint64_t)
    int32_t width;                  // in the offset 8 (from init_context read of addresses)
    int32_t height;                 // in the offset 12 (from init_context read of addresses)

    int* framebuffer;               // in the offset 16 (gfx_render), potentially switch to uint8_t*
    // if we can't find any more arguments, do padding with unused bytes
    // uint8_t padding[1048];       // 1072 - 8 - 4 - 4 - 900 - 8 = 1048 bytes of padding to fill the struct to 1072 bytes
    uint64_t window_addr;           // in the offset 1064 (0x428) of this struct to later use in gfx_close (from gfx_close read of addresses)
} gfx_context;

// gfx_loop                     -- void, ktoremu podaje sie 1 argument (pewnie z tym calym contextem) -- potem okno zaincjalizowane w loopie rysuje animacje
// gfx_render
// gfx_create_context

/** 
 * Since we multiply two numbers by each other and then by 4, it's likely 
 * allocation of a framebuffer for an image WxH with 4 bytes per pixel (RGBA).
 * Since malloc is called as the last operation of void*, 
 * function returns the allocated pointer of desired type and size.
 * size_t size = arg->W * arg->H * 4;
 * return malloc(size);
 */
void* gfx_allocate_framebuffer(void* arg);

/** 
 * Function that takes a pointer to gfx_context struct (safely, let's say void*),
 * and upon retrieving the Uid for close instruction, sends the information 
 * to window which is addressed at offset 1064 (0x428) of the struct to close the window. 
 */
void gfx_close(void* ctx);

/**
 * Function saves it's arguments on the stack and calls memset(void* str, int c, size_t n),
 * that fills the first `n` bytes of the address pointed by `str` with the character `c`.
 * In our decoded assembly c=0, n=1072 and str is pointer to gfx_context,
 * so our context struct will have exactly 1072 bytes of later used memory
 * (created window pop-up is addressed by pointer at offset 1064 of this struct).
 * Before calling this function, ctx has to already be allocated in memory.
 */
void* gfx_create_context(void* ctx, int32_t width, int32_t height, uint64_t name_addr);

/** 
 * Functions, that all work the same way.
 * Upon invocation, they return some hardcoded values:
 * - gfx_get_height_screen returns 300
 * - gfx_get_width_screen returns 300
 * - gfx_get_window_title returns "Challenge"
 * Since gfx_get_window_title returns a pointer to a string,
 * we're safe to read it and return it as int64_t.
 * Later if wanted to output as string, we would read from beginning of that address.
 */
int32_t gfx_get_height_screen(void);
int32_t gfx_get_width_screen(void);
int64_t gfx_get_window_title(void);

/** 
 * High-level function, that based on input pointer to the context struct, 
 * initializes the whole graphics context and window.
 * I won't talk much about it, as it has a lot of outside functions, 
 * but it helped me to better understand the layout of the gfx_context, 
 * especially with gfx_create_context function and layout/type of it's arguments.
 */
void gfx_init_context(void* ctx);

/**
 * 
 */
void gfx_loop(void* ctx);

/**
 * Function reads input arguments and based on the height of the window
 * calculates the position that "You did it! :D" will later be displayed.
 * Then it loops over int* framebuffer until iterator of the loop 
 * isn't equal to width*height and fills every framebuffer[i] 
 * (pixel, every element has 4 bytes) with color value 0x101010 (which is dark gray).
 * When the loop ends, function jumps to section in which the draw_text is called
 * with passing gfx_context pointer, string "You did it! :D", render position, 
 * calculated height and color in which message will be displayed (0xFF00 - bright green).
 * If the flag is set to 0, function returns after drawing the text.
 * If not, then based on function making operation of floating points 
 * implements looping horizontal motion for the text on the screen.
 * (My deduction is, that it's related to the `Bonus` mentioned in the task description).
 */
void gfx_render(void* ctx, int flag);

/** 
 * Takes 1 argument and creates local struct timespec* tp; 
 * Then it sets tp->tv_sec = input_arg / 1000
 * and tp->tv_nsec = (input_arg % 1000) * 1000000.
 * At last it loads 0 (NULL) as second argument to nanosleep,
 * calls nanosleep(tp, NULL) and returns;
 * If we would want program to sleep for 1 second,
 * we should call gfx_sleep(1000);
 */
void gfx_sleep(long arg);

/** 
 * Calls clock_gettime(NULL, tp) where tp is timespec* struct.
 * after retrieving the information, it calculates time in milliseconds
 * converting read seconds and nanoseconds to milliseconds:
 * eg. tp->tv_sec * 1000 + tp->tv_nsec / 1000000
 */
int gfx_time(void); 

#endif // RENDER_H
