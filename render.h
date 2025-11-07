// render.h

#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdint.h>

/** 
 * Arguments to functions are passed in following order of registers:
 * 1. rdi, 2. rsi, 3. rdx, 4. rcx, 5. r8, 6. r9
 * Result of function is stored in rax or if pointer was passed,
 * then it is saved in respective pointer from input arguments.
 * (*) 7th and next are Passed on the stack in reverse order,
 * so the last argument is the first one pushed onto the stack.
 * Float arguments are passed in separate floating-point registers (%xmm{..}).

 * Ints are 32 bits registers - eax, ebx, ecx, edx, esi, edi.
 * Longs/pointers are 64 bits - rax, rbx, rcx, rdx, rsi, rdi.
 */

/** 
 * gfx_context is our core central C data structure, that manages the window's state. 
 * All attributes has been named according to their purpose. This structure is of size 
 * 1072, which we can deduct from the memset in the gfx_create_context function
 * and that the furthest reference to memory in this struct is at offset 1064 (0x428),
 * which occurs very often in the gfx functions. As we can notice in gfx_init_context,
 * where the value is saved, that it's the address of the NSWindow, that we will operate on.
 * 1064 (furthest used offset) + 8 (size of that pointer) = 1072 bytes total size of struct.
 * 
 * - name_addr   - address to the window title string, which is at offset 0 (0x0), 
 *                 which we deduct from gfx_init_context execution and 
 *                 gfx_create_context layout of the arguments.
 * - width       - display width at offset 8 (0x8), deducted from 
 *                 gfx_init_context and gfx_create_context.
 * - height      - display height at offset 12 (0xC), deducted from 
 *                 gfx_init_context and gfx_create_context; the right order in this struct 
 *                 of width and height was deducted from CGRectMake call in gfx_init_context
 *                 and the arguments order that CGRectMake takes
 * - framebuffer - pointer to allocated buffer at offset 16 (0x10), deducted from
 *                 gfx_render and draw_char and later just confirmed by gfx_allocate_framebuffer,
 *                 that it's the pointer to framebuffer of ints (pixels, shown at the screen)
 *                 allocated for the window of size (width x height) with 4 bytes per pixel (RGBA)
 *                 (since memory allocated is width*height*4 bytes, where sizeof(int) == 4).
 * - something1  - at offset 1048 (0x418), deducted from gfx_loop function,
 * - something2  - at offset 1052 (0x41C), deducted from gfx_loop function,
 * - something3  - at offset 1056 (0x420), deducted from gfx
 * - something4  - at offset 1060 (0x424), deducted from gfx_loop function,
 * - window_addr - at offset 1064 (0x428), first deducted from gfx_close, 
 *                 where value at offset 1064 is called and taken as argument
 *                 to Objective-C method call to send a close message.
 *                 Later from gfx_init_context, I confirmed that my deduction was correct,
 *                 since we can notice a save on the address of the first argument (rdi)
 *                 to the same offset 1064 of our struct, which is the NSWindow address, 
 *                 which was created upon calling NSWidow with alloc method,
 *                 just before calling initWithContentRect:styleMask:backing:defer: method.
 */
typedef struct gfx_context {
    uint64_t name_addr;
    int32_t width;
    int32_t height;

    int* framebuffer;
    
    int something1;                 // in the offset 1048 (0x418) (from gfx_loop), value saved in cases 10 and 11 of switch (modifierFlags)
    int something2;                 // in the offset 1052 (0x41C) (from gfx_loop), value saved in cases 5 and 6 of switch (locationInWindow)
    int something3;                 // in the offset 1056 (0x420) (from gfx_loop), value saved in cases 5 and 6 of switch (locationInWindow)
    int something4;                 // in the offset 1060 (0x424) (from gfx_loop), value saved in cases 1 and 2 of switch (?)

    uint64_t window_addr;
} gfx_context;

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
void gfx_create_context(void* ctx, int32_t width, int32_t height, uint64_t name_addr);

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
const int32_t  gfx_get_height_screen(void);
const int32_t  gfx_get_width_screen(void);
const uint64_t gfx_get_window_title(void);

/** 
 * High-level function, that based on input pointer to the context struct, 
 * initializes the whole graphics context and window.
 * I won't talk much about it, as it has a lot of outside functions, 
 * but it helped me to better understand the layout of the gfx_context, 
 * especially with gfx_create_context function and layout/type of it's arguments.
 */
void gfx_init_context(void* ctx);

/**
 * I don't think it's exactly a 'loop', but it's definitely a switch with 11 cases
 * It modifies elements of the gfx_context only in cases 1,2,5,6,10,11 of switch,
 * other cases, so: 3,4,7,8,9 and default, does not modify any of the values.
 * 
 * 
 * At the end returns 0.
 */
int gfx_loop(void* ctx);

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
