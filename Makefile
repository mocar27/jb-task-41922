.PHONY : all debug linux clean

all : main 

# using aarch64
main: main.c
	cc -o $@ $^ -lrender -L. -framework Cocoa -framework AudioToolbox 

debug: main.c
	cc -o $@ $^ -Wall -Wextra -g -lrender -L. -framework Cocoa -framework AudioToolbox 

linux: main.c
	cc -o $@ $^ -lrender -L. -lX11 -lasound

clean:
	rm -f main debug