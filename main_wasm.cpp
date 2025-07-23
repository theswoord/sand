#include "sand.hpp"
#include <emscripten.h>

//  std::random_device rd;

// emcc main_linux.cpp sand.cpp -o your_game.html -s USE_SDL=2 -s SDL2_IMAGE_FORMATS="['png','jpg']" -s USE_WEBGL2=1
//   emrun your_game.html

// emcc main_wasm.cpp sand.cpp -o new.html -s USE_SDL=2 -s SDL2_IMAGE_FORMATS="['png','jpg']" -s USE_WEBGL2=1
// emrun test.html --no-browser

// emcc main_wasm.cpp sand.cpp \
//     -o reactgame.js \
//     -s USE_SDL=2 \
//     -s SDL2_IMAGE_FORMATS="['png','jpg']" \
//     -s USE_WEBGL2=1 \
//     -s WASM=1 \
//     -s MODULARIZE=1 \
//     -s EXPORT_ES6=1 \
//     -s INVOKE_RUN=0 \
//     -s NO_EXIT_RUNTIME=1 \
//     -s EXPORTED_RUNTIME_METHODS='["cwrap", "ccall", "getValue", "setValue", "UTF8ToString"]' \
//     -s ALLOW_MEMORY_GROWTH=1 \
//     -s INITIAL_MEMORY=64MB


// emcc main_wasm.cpp sand.cpp \
//     -o reactgame.js \
//     -O3 \
//     -s USE_SDL=2 \
//     -s SDL2_IMAGE_FORMATS="['png','jpg']" \
//     -s USE_WEBGL2=1 \
//     -s WASM=1 \
//     -s MODULARIZE=1 \
//     -s EXPORT_ES6=1 \
//     -s ENVIRONMENT=worker \
//     -s INVOKE_RUN=0 \
//     -s ALLOW_MEMORY_GROWTH=1 \
//     -lembind

// emcc main_wasm.cpp sand.cpp \
//     -o reactgame.js \
//     -O3 \
//     -s USE_SDL=2 \
//     -s WASM=1 \
//     -s MODULARIZE=1 \
//     -s EXPORT_ES6=1 \
//     -s INVOKE_RUN=0 \
//     -s ALLOW_MEMORY_GROWTH=1 \
//     -lembind

void PrintKeyInfo(SDL_KeyboardEvent *key)
{
    /* Is it a release or a press? */
    if (key->type == SDL_KEYUP)
        printf("Release:- ");
    else
        printf("Press:- ");

    /* Print the hardware scancode first */
    printf("Scancode: 0x%02X", key->keysym.scancode);
    /* Print the name of the key */
    printf(", Name: %s", SDL_GetKeyName(key->keysym.sym));
    /* We want to print the unicode info, but we need to make */
    /* sure its a press event first (remember, release events */
    /* don't have unicode info                                */
    if (key->type == SDL_KEYDOWN)
    {
        /* If the Unicode value is less than 0x80 then the    */
        /* unicode value can be used to get a printable       */
        /* representation of the key, using (char)unicode.    */
        printf(", Name: %s", SDL_GetKeyName(key->keysym.sym));
    }
    printf("\n");
}


typedef struct main_wasm
{
    Uint32 frameStart;
    SDL_Event e;
    bool quit;
    bool hold;
    int x;
    int y;
    int mousex;
    int mousey;
    std::vector<std::vector<char>> themap;
    // SDL_Window *window = nullptr;
    SDL_Surface *screenSurface;
    SDL_Rect rectangle;
    SDL_Rect particle;
    int frameTime;
    int targetFPS;
    int frameDelay;
    int element;
    SDL_Window *window;
} t_wasm;
t_wasm *wasm = nullptr;


extern "C" {
  EMSCRIPTEN_KEEPALIVE
  void cleanup() {
    //   printf("C++ cleanup function called directly!\n");

    SDL_DestroyWindow(wasm->window);
    SDL_Quit();
    emscripten_cancel_main_loop();
    delete wasm;
      fflush(stdout); // Force output to flush to the console

    //   SDL_DestroyRenderer(renderer);

  }
}


// void free_all(t_wasm *wasm)
// {
//     SDL_DestroyWindow(wasm->window);
//     SDL_Quit();
    
//     delete wasm;
// }

void element_picked(t_wasm *wasm, std::string str)
{
        static std::random_device rd; // Obtain a seed from the hardware
static std::mt19937 gen(rd()); // Seed the generator
    if (str == "E")
    {
        int element;
        element = gen() % 4 + 1;
        if(element != wasm->element) // hadi ghir zayda
        wasm->element = element;
    }
    
    if (str == "1")
    {
        // printf("khtarit sand \n");
        wasm->element = SAND;

        /* code */
    }
    else if (str == "2")
    {
        // printf("khtarit ROCK \n");

        wasm->element = ROCK;

        /* code */
    }
    else if (str == "3")
    {
        // printf("khtarit WATER \n");

        wasm->element = WATER;

        /* code */
    }
    else if (str == "4")
    {
        // printf("khtarit LADY \n");

        wasm->element = LADY;

        /* code */
    }
    else if (str == "0")
    {
        wasm->element = EMPTY;

        /* code */
    }
        else if (str == "5")
    {
        wasm->element = SPONGE;

        /* code */
    }
        else if (str == "6")
    {
        wasm->element = EMPTY;

        /* code */
    }
        else if (str == "8")
    {
        wasm->element = EMPTY;

        /* code */
    }
        else if (str == "9")
    {
        wasm->element = EMPTY;

        /* code */
    }


}
Uint32 element_color(t_wasm *wasm)
{

     Uint8 r = 0, g = 0, b = 0; // Initialize for safety

    if (wasm->element == ROCK)
    {
        r = 0x7F; g = 0x83; b = 0x86; // Example: a grayish rock
    }
    else if (wasm->element == SAND)
    {
        r = 0xF2; g = 0xD2; b = 0xA9; // Example: sand
    }
    else if (wasm->element == WATER)
    {
        r = 0x99; g = 0xC0; b = 0xE3; // Example: water
    }
    else if (wasm->element == WETSAND)
    {
        r = 0xAE; g = 0x8F; b = 0x60; // Example: water
    }
    else if (wasm->element == ZINJAR)
    {
        r = 0xA1; g = 0xBA; b = 0xA1; // Example: water
    }
        else if (wasm->element == SPONGE)
    {
        r = 0xFD; g = 0xFE; b = 0x03; // Example: water
    }
    else if (wasm->element == LADY)
    {
        r = 0xFF; g = 0xA5; b = 0x00; // Your desired orange (255, 165, 0)
    }
    else // Default to white
    {
        r = 0xFF; g = 0xFF; b = 0xFF;
    }

    return SDL_MapRGB(wasm->screenSurface->format, r, g, b);
}

void init_window(std::vector<std::vector<char>> &map)
{

    int logicalW = WWIDTH / sandsize;
    int logicalH = WHEIGHT / sandsize;
    map.resize(logicalH);

    for (int y = 0; y < logicalH; ++y)
    {
        map[y].resize(logicalW, EMPTY);
    }
}

int init_all(t_wasm *wasm)
{
    wasm->frameStart = 0;
    wasm->quit = false;
    wasm->hold = false;
    wasm->x = 0;
    wasm->y = 0;
    wasm->mousex = 0;
    wasm->mousey = 0;
    // std::vector<std::vector<char> > themap;
    wasm->window = nullptr;
    wasm->screenSurface = nullptr;
    wasm->rectangle = {0, 0, 10, 10};
    wasm->particle = {0, 0, sandsize, sandsize};
    wasm->frameTime = 0;
    wasm->targetFPS = 60;
    wasm->element = WATER; // water to debug
    wasm->frameDelay = 1000 / wasm->targetFPS;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return 1;
    }

    wasm->window = SDL_CreateWindow("miw", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN);
    if (wasm->window == nullptr)
    {
        // std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    wasm->screenSurface = SDL_GetWindowSurface(wasm->window);
    if (wasm->screenSurface == nullptr)
    {
        // std::cerr << "Screen surface could not be obtained! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(wasm->window);
        SDL_Quit();
        return 1;
    }
    init_window(wasm->themap);

    return 0;
}

void wasm_loop(void *ptr)
{
    t_wasm *wasm;
    wasm = static_cast<t_wasm *>(ptr);
    wasm->frameStart = SDL_GetTicks();

    while (SDL_PollEvent(&wasm->e))
    {
        if (wasm->e.type == SDL_QUIT)
        {
            wasm->quit = true;
        }
        if (wasm->e.type == SDL_MOUSEBUTTONDOWN)
        {
            wasm->hold = true;
        }
        if (wasm->e.type == SDL_MOUSEBUTTONUP)
        {
            wasm->hold = false;
        }
        if (wasm->e.type == SDL_KEYDOWN)
        {

            // wasm->e.key.keysym.sym
            std::string number = SDL_GetKeyName(wasm->e.key.keysym.sym);
            // if(!SDL_strcmp( SDL_GetKeyName( wasm->e.key.keysym.sym ),"1") || !SDL_strcmp( SDL_GetKeyName( wasm->e.key.keysym.sym ),"2") ||!SDL_strcmp( SDL_GetKeyName( wasm->e.key.keysym.sym ),"3") ||!SDL_strcmp( SDL_GetKeyName( wasm->e.key.keysym.sym ),"4") ||!SDL_strcmp( SDL_GetKeyName( wasm->e.key.keysym.sym ),"0"))
            // {
            element_picked(wasm, number);
            // }
            if (!SDL_strcmp(SDL_GetKeyName(wasm->e.key.keysym.sym), "R")) // 0 optimisation
            {
                random_sand_gen(wasm->themap);
            }

            // PrintKeyInfo(&wasm->e.key);
        }
    }
    if (wasm->hold)
    {
        SDL_GetMouseState(&wasm->mousex, &wasm->mousey);
        int logicalX = wasm->mousex / sandsize;
        int logicalY = wasm->mousey / sandsize;

        int logicalW = WWIDTH / sandsize;
        int logicalH = WHEIGHT / sandsize;

        if (logicalY >= 0 && logicalY < logicalH && logicalX >= 0 && logicalX < logicalW&&wasm->element == EMPTY)
        {
            wasm->themap[logicalY][logicalX] = wasm->element;
        }
        
       else if (logicalY >= 0 && logicalY < logicalH && logicalX >= 0 && logicalX < logicalW && wasm->themap[logicalY][logicalX] == EMPTY )
        {
            wasm->themap[logicalY][logicalX] = wasm->element;
        }
    }

    SDL_GetMouseState(&wasm->mousex, &wasm->mousey);

    wasm->rectangle.x = wasm->mousex - wasm->rectangle.w / 2;
    wasm->rectangle.y = wasm->mousey - wasm->rectangle.h / 2;
    update_position_neo(wasm->themap);

    SDL_FillRect(wasm->screenSurface, NULL, SDL_MapRGB(wasm->screenSurface->format, 0, 0, 0));

    // printf("Color being used: 0x%X\n", element_color(wasm));

    SDL_FillRect(wasm->screenSurface, &wasm->rectangle, element_color(wasm));

    show_sand_neo(wasm->screenSurface, &wasm->particle, wasm->themap);

    SDL_UpdateWindowSurface(wasm->window);
    wasm->frameTime = SDL_GetTicks() - wasm->frameStart;
    if (wasm->frameDelay > wasm->frameTime)
    {
        SDL_Delay(wasm->frameDelay - wasm->frameTime);
    }
    // }
}

int main()
{
    wasm = new t_wasm;
    if (init_all(wasm) != 0)
    {
        delete wasm;
        return 1;
    }

    emscripten_set_main_loop_arg(wasm_loop, wasm, wasm->targetFPS, 1);
    
    return 0;
}