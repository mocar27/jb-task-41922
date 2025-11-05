// render.h

#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>

#define EXIT_SUCCESS 0

// Arguments to functions are passed in following order of registers
// rdi, rsi, rdx, rcx, r8, r9
// Result of function is stored in rax or if pointer was passed,
// then it is saved in respective pointer from input arguments.

// Operating on struct timespec* inside some functions.

// ints are 32 bits registers - eax, ebx, ecx, edx, esi, edi, ebp, esp
// longs are 64 bits - rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp
// pointers are 64 bits - rax, rbx, rcx, rdx?

// some struct to operate on the window's state

// gfx_allocate_framebuffer     -- void ktory przyjmuje 1 argument
// gfx_close                    -- void ktory przyjmuje 1 argument calling XCloseDisplay with struct that is a Display*
// gfx_create_context           -- non-void? przyjmuje 4 argumenty
// gfx_init_context             -- void, ktoremu podaje sie wskaznik (1 argument) i on zapisuje wynik na ten wskaznik
// gfx_loop                     -- void, ktoremu podaje sie 1 argument (pewnie z tym calym contextem)
// gfx_render                   -- void, ktoremu podaje sie 2 argumenty

// These just return some hard-coded screen properties
int gfx_get_height_screen(void);
int gfx_get_width_screen(void);
char* gfx_get_window_title(void);

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
