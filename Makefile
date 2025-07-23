srcs = main.cpp
objs = main.objs
libs = -D_THREAD_SAFE -I/opt/homebrew/include -I/opt/homebrew/include/SDL2


all :
	# $(CPP) 
	g++ main.cpp sand.cpp -o sand `pkg-config --libs sdl2` `pkg-config --cflags sdl2` ; ./sand


linux :
	g++ -o sand_linux main_linux.cpp sand.cpp `sdl2-config --cflags --libs`


wasme :
	emcc main_wasm.cpp sand.cpp     -o ../react_wasm/sand-app/src/game/reactgame.js \
	-s USE_SDL=2 \
	-s WASM=1 \
	-O3 \
	-s MODULARIZE=1 \
	-s EXPORT_ES6=1 \
	-s INVOKE_RUN=0 \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s EXPORTED_RUNTIME_METHODS="['callMain']" \
	-s INITIAL_MEMORY=64MB \
	-s USE_WEBGL2=1 \
	-s EXIT_RUNTIME=1
#➜  ~ pkg-config --cflags sdl2
#-D_THREAD_SAFE -I/opt/homebrew/include -I/opt/homebrew/include/SDL2

#➜  ~ pkg-config --libs sdl2
#-L/opt/homebrew/lib -lSDL2