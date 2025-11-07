# jb-task-41922 solution Konrad Mocarski

During finishing my solution and connecting all the functions to retrieve `main.c`, I've encountered a problem with testing it.
I got the main problem with gfx_create_context, as to my understanding, it was not complicated function, yet 
every time I was invoking it, then memset was correctly invoked inside, but I felt like assigning of the arguments were not.
Every time out of gfx_context_create it came out as bunch of zeros or with just height being well initialized, 
even tho arguments were passed in order according to read/assign of them in gfx_context_create.

At first I thought there's a problem with memory addressing, so I've tried to pass not values, but addresses and 
I have even created my own function in C, that does the same as provided compiled gfx_context_create, decompiled it
and the assign of the arguments worked there. I've tried switching the function from `void` to `void*` and assign
the return value again the the gfx_context* (as rax is inside function used to assign value of 1st argument to it),
but it did not work either. If I'm mistaken, then I would really really love the solution to it; I got really soaked up into the task, 
that it felt somewhat empty when I couldn't test it, because of some small bug I may not have noticed.

## Explanation

### Tools used

- ***IDA Free*** - to decompile binary file into ASM code to make it somewhat readable 
and to be able to retrieve all the information that I've provided in my solution that has let me to somewhat solve this task.
- ***https://godbolt.org*** - Compiler Explorer, that let's you to check what assembly code is generated for given C functions.
- ***x64dbg*** - I wanted to also use this program, but it wouldn't let me load the binaries, as they were in the invalid 
format to load into this application. This was kind of sad, since x64dbg let's you actively check for register changes with each line
of execution, so it would might have helped me solve my problem mentioned above.

### Functions deduction

The quickest way I came up with identifying key functions, I think was the `Exports` tab in IDA. I've additionally iterated over every function,
that IDA has pointed out to me, in case I would have missed something, but the functions in `Exports` with prefix `gfx_`, where indeed the functions
I was looking for. Every `gfx_` function also had `public` suffix at the beginning, so it made a clear mark to me.

When it comes to function's arguments deduction, knowing how and in what registers are which arguments passed to the function,
we could quickly deduct the number of arguments each function takes (based on usage of `r*` or `e*` registers we can also deduct their type). 
Based on whether at the end of each function register `rax` is used to save the output of the function, we can deduct also the return and it's type.

After seeing most of the time, that first argument is saved to the stack and then later it's invoked a few times in a few functions,
I've deducted, that the 1st argument in these functions would be our 'central C struct'. 
I have made a deep dive into every function inside execution in the `render.h` included file. 

### Core Data Structure deduction

Upon investigating some of the functions, I quickly got the idea, that our main struct is passed (when it's passed),
to key functions as first argument. Then, connecting the dots from this and with the idea of at what time, what arguments
are read and passed to functions like `setTitle:` or `CGRectMake` and in what order, I've tried to deduct the layout of 
our core central C structure. 

- from `gfx_create_context` we realise the size of the struct, which is 1072, which makes sense, since the last attribute 
of the struct is at offset 1064 of our struct and is with a size of 8 bytes, which is 1064 + 8 = 1072.
- `setTitle:` and `stringWithUTF8String:` in `gfx_init_context` made me realise, that in our structure the title of the window
is the first attribute and it's an address to the string, as it goes from offset 0 to offset 8 in the structure.
- `CGRectMake` in `gfx_init_context` and `gfx_create_context` made me realise the layout of width/height in the struct,
since these are saved to memory in `gfx_create_context` in SOME order, but then when they are read and passed as arguments
to `CGRectMake`, we can deduct which one is the 2nd attribute and which one is the 3rd attribute 
(these attributes are ints, which takes 4 bytes of memory, in memory respectively at the offset 8 and 12 of the struct).
- `gfx_render` made me realise, that at the offset 16 of the struct (4th attribute), there is a framebuffer for the window,
that is filled by ints (pixels) in that function, up until reaching a certain threshold.
Additionally we have a function `gfx_allocate_buffer`, which allocates that buffer with malloc.

- `gfx_loop` being the main loop that operates on our created window, it reads all the events from the Cocoa
queue and based on the event that occured, it performs related operation (switch/case with 11 cases). 
It performs operations until receving event=0, which is recognized as event to close the window. 
Upon receiving it, inside `gfx_close` the event is sent to the window to close gracefully. 
`gfx_loop` operates on a few struct attributes, that we deducted from it's execution, as it marks 
the occurances of events (LMB pressed/released, Mouse Moved, Left Mouse Dragged, Key Up/Down), 
so we create additional attributes to log these events with offsets read from the references
to our struct (that is the 1st and only argument to this function).

- `gfx_close` made me realise and `gfx_init_context` made me confirm my theory, that at the offset 1064 
and of the size of 8 bytes (which sums up to exactly 1072) there is the last attribute of the struct, 
and that is the NSWindow address, that we will call over the whole execution and send messages to the window 
and at the end we will send msg to close it.

If this explanation is too short or not clear enough, please refer to the included with solution `render.h` file,
where I've made a deep dive with each of the struct's attribute, where I got the idea from for each attribute
and how I came up with exactly that layout.

### Any rest additional information

When it comes to computer graphics, I'm currently in the process of learning it's ideas
and fundamentals, as well as, in the process of learning OpenGL.

When it comes to this task, gained experience from different fields of Computer Science mentioned below has made me 
somewhat look at the bigger picture, when it comes to developing software and provided me with
important knowledge, that has helped me with somewhat solving this Jetbrains internship task.

I've used my combined knowledge from: 
- ***Security of computer systems*** - when it comes to reverse-engineering and writing/understanding code based on compiler binary 
(additional materials related to task I was working on is included in `materials/`).
- [Operating systems](https://github.com/mocar27/MIMUW/tree/main/IV%20semester/os) - when it comes to assembly, decompilation and all the registers/stack operations in ASM.
- [Compiler constructions](https://github.com/mocar27/latte-compiler) (additionally to OS) - when it comes to 
understanding generated code by the compiler and all the decompiled instructions.

## Reference 

The task and initial library was taken from [here](https://github.com/gabryon99/jb-internship-2025-material).
