# jb-task-41922 solution Konrad Mocarski

## Explanation
A brief explanation of your process. This is the most important part. Describe the tools you used, how you identified the key functions, and how you determined the fields and layout of the main.
- using x64gdb (wanted to, but it didn't want to cooperate)
- using ida free 
- https://godbolt.org (Compiler explorer, który pozwala sprawdzić jaki asembler generują różne wersje kompilatorów dla danego kod)


## Additional materials
As pointed out in the task description, I've included in the `materials` directory any additional information or projects I've encountered
during my programming journey.

## Task
- [ ] **Discover the API**: Inspect the librenderer.dylib binary to identify the public functions it provides. From their names, deduce their purpose and how they work together.
- [ ] **Reconstruct the Core Data Structure**: The library's functions likely operate on a central C struct to manage the window's state. You will need to reverse-engineer the layout of this struct in your own code to interface with the library correctly.
- [ ] **Implement main.c**: Write a C program that uses the discovered API to correctly initialize the library, run its main loop, and properly shut it down. If you succeed, an animation will appear in the window.
- [ ] **Compile and Link**: Compile your main.c and link it against librenderer.dylib to create the final executable.

***Bonus***
- [ ] If you like "challenges", are you able to activate the program's animation? :)