all:
	gcc main.c -o main $(shell pkg-config --cflags --libs sdl2) -g -O0 -lSDL2_image -lpthread
    

