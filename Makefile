srcs = main.cpp
objs = main.objs
libs = -D_THREAD_SAFE -I/opt/homebrew/include -I/opt/homebrew/include/SDL2


all :
	# $(CPP) 
	g++ main.cpp sand.cpp -o sand `pkg-config --libs sdl2` `pkg-config --cflags sdl2` ; ./sand



#➜  ~ pkg-config --cflags sdl2
#-D_THREAD_SAFE -I/opt/homebrew/include -I/opt/homebrew/include/SDL2

#➜  ~ pkg-config --libs sdl2
#-L/opt/homebrew/lib -lSDL2