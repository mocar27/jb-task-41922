// render.h

#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>

#define EXIT_SUCCESS 0

// Arguments to functions are passed in following order of registers
// rdi, rsi, rdx, rcx, r8, r9
// Result of function is stored in rax or if pointer was passed,
// then it is saved in respective pointer from input arguments.

// 7th and next are Passed on the stack in reverse order, so the last argument is the first one pushed onto the stack.
// Floating-point arguments: Passed in separate floating-point registers (%xmm0 through %xmm7). 

// Ints are 32 bits registers - eax, ebx, ecx, edx, esi, edi.
// Longs/pointers are 64 bits - rax, rbx, rcx, rdx, rsi, rdi.

// time i sleep sa pewnie potrzebne zeby to okno od razu sie nie zamknelo

// gfx_context has size of 1072 and it makes sense, since in gfx_close there is a call to address stored in this struct
// with the offset of 1064 (428h in gfx_close reference), this value is assigned in gfx_init_context function
typedef struct gfx_context {
    char* name;                     // in the offset 0 (from init_context read of addresses)
    int32_t width;                  // in the offset 8 (from init_context read of addresses)
    int32_t height;                 // in the offset 12 (from init_context read of addresses)

    // if we can't find any more arguments, do padding with unused bytes
    uint8_t padding[1040];          // 1072 - 32 = 1040 bytes of padding to fill the struct to 1072 bytes
    uint64_t window_addr;           // in the offset 1064 (0x428) of this struct to later use in gfx_close (from gfx_close read of addresses)
} gfx_context;

// gfx_loop                     -- void, ktoremu podaje sie 1 argument (pewnie z tym calym contextem) -- potem okno zaincjalizowane w loopie rysuje animacje
// gfx_render
// gfx_create_context
void gfx_loop(void* arg);
// data to prawdopodobnie context, a ten int jest nic niewarty, bo potem (juz po wyprintowaniu "You did it!")
// sprawdzane jest czy on jest 0, jesli tak to dzieje sie cos jeszcze, jesli nie to program sie konczy - moze to jest animacja ta z bonusa?
// void gfx_render(void* data, int ); -- void, ktoremu podaje sie 2 argumenty --  render na koniec / przed zamknieciem okna

// Since we multiply two numbers by each other and then by 4, it's likely 
// allocation of a framebuffer for an image of width `w` and height `h` with 4 bytes per pixel (RGBA).
// Allocates framebuffer given as attributes of an input struct pointer
// Since malloc is called as the last operation of void*, it returns the allocated pointer of desired type and size.
// int x = arg->w;
// int y = arg->h;
// size_t size = x * y * 4;
// return malloc(size);
void* gfx_allocate_framebuffer(void* arg);

// Function that takes a pointer to gfx_context struct (safely, let's say void*),
// and upon retrieving the Uid for close instruction, sends the information 
// to window which is addressed at offset 1064 (0x428) of the input struct to close the window;
void gfx_close(void* ctx);

// Function reads all it's input arguments saves it on the stack, then calls memset(void* str, int c, size_t n) 
// that copies the character `c` to the first `n` characters of the address pointed by `str`.
// In our decoded assembly c=0, n=1072 and str is input pointer to gfx_context,
// so our context struct will have exactly 1072 bytes of later used memory
// (created window pop-up is addressed by pointer at offset 1064 of this struct).
void gfx_create_context(void* ctx, int32_t width, int32_t height, char* name);

// These just return some hard-coded screen properties
int32_t gfx_get_height_screen(void);
int32_t gfx_get_width_screen(void);
char* gfx_get_window_title(void);

// High-level function, that based on input pointer to the context struct, initializes the whole graphics context and window.
// I won't talk much about it, as it has a lot of outside functions, but it helped me to better understand the layout
// of the gfx_context, expecially with gfx_create_context function and layout of it's arguments.
void gfx_init_context(void* ctx);

// Takes 1 arguments, creates local struct timespec* tp; 
// Seconds is input_arg / 1000, nanoseconds is (input_arg % 1000) * 1000000;
// store tp->tv_sec = rax // (input arg / 1000);
// store tp->tv_nsec = rax // (input arg % 1000 * 1000000);
// Load 0 (NULL), as second argument to nanosleep, so call nanosleep(tp, NULL) and return;
void gfx_sleep(long nanoseconds);

// Calling clock_gettime(NULL, tp);
// int x = tp->tv_sec * 1000; // Convert read seconds to milliseconds;
// int y = tp->tv_nsec / 1000000; // Convert read nanoseconds to milliseconds;
// return y + z;
int gfx_time(void);

#endif // RENDER_H
