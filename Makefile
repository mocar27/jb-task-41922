.PHONY : all debug clean

all : main 

# using aarch64
main: main.c
	cc -o $@ $^ -lrender -L. -framework Cocoa -framework AudioToolbox 

debug: main.c
	cc -o $@ $^ -Wall -Wextra -g -lrender -L. -framework Cocoa -framework AudioToolbox 

clean:
	rm -f main debug