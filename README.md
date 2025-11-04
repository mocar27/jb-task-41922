# jb-task-41922



## Task
- [ ] Discover the API: Inspect the librenderer.dylib binary to identify the public functions it provides. From their names, deduce their purpose and how they work together.
- [ ] Reconstruct the Core Data Structure: The library's functions likely operate on a central C struct to manage the window's state. You will need to reverse-engineer the layout of this struct in your own code to interface with the library correctly.
- [ ] Implement main.c: Write a C program that uses the discovered API to correctly initialize the library, run its main loop, and properly shut it down. If you succeed, an animation will appear in the window.
- [ ] Compile and Link: Compile your main.c and link it against librenderer.dylib to create the final executable.

***Bonus***
- [ ] If you like "challenges", are you able to activate the program's animation? :)