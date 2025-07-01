#include "sand.hpp"
#include <emscripten.h>

//  std::random_device rd;

//emcc main_linux.cpp sand.cpp -o your_game.html -s USE_SDL=2 -s SDL2_IMAGE_FORMATS="['png','jpg']" -s USE_WEBGL2=1
//  emrun your_game.html
void clear_window()
{
}
typedef struct main_wasm
{
     Uint32 frameStart ;
    SDL_Event e;
    bool quit ;
    bool hold ;
    int x ;
    int y ;
    int mousex ;
    int mousey ;
    std::vector<std::vector<char> > themap;
    // SDL_Window *window = nullptr;
    SDL_Surface *screenSurface;
    SDL_Rect rectangle ;
    SDL_Rect particle;
    int frameTime;
    int targetFPS;
    int frameDelay ; 
    SDL_Window *window ;
} t_wasm; 

void init_window(std::vector<std::vector<char> > &map)
{
    // std::vector<char> line;
    // int x,y;
    // x=0;
    // y=0;

    // while (y < WHEIGHT)
    // {
    //     x=0;
    //     while (x < WWIDTH)
    //     {
    //         line.push_back(EMPTY);
    //         x++;
    //     }
    //     map.push_back(line);
    //     line.clear();
    //     y++;
    // }
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
    wasm->screenSurface =nullptr;
    wasm-> rectangle = {0, 0, 25, 25};
    wasm-> particle = {0, 0, sandsize, sandsize};
    wasm-> frameTime = 0;
    wasm->targetFPS = 60;
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
    t_wasm * wasm;
    wasm = static_cast<t_wasm*> (ptr); 
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
        }
            if (wasm->hold)
            {
                SDL_GetMouseState(&wasm->mousex, &wasm->mousey);
                int logicalX = wasm->mousex / sandsize;
                int logicalY = wasm->mousey / sandsize;

                int logicalW = WWIDTH / sandsize;
                int logicalH = WHEIGHT / sandsize;

                if (logicalY >= 0 && logicalY < logicalH && logicalX >= 0 && logicalX < logicalW)
                {
                    wasm->themap[logicalY][logicalX] = SAND;
                }
            }

        SDL_GetMouseState(&wasm->mousex, &wasm->mousey);

        wasm->rectangle.x = wasm->mousex - wasm->rectangle.w / 2;
        wasm->rectangle.y = wasm->mousey - wasm->rectangle.h / 2;
        update_position_neo(wasm->themap);

        SDL_FillRect(wasm->screenSurface, NULL, SDL_MapRGB(wasm->screenSurface->format, 0, 0, 0));

        SDL_FillRect(wasm->screenSurface, &wasm->rectangle, SDL_MapRGB(wasm->screenSurface->format, 0xC2, 0xB2, 0x80));

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

    t_wasm *wasm = new t_wasm;
    // SDL_memset(wasm,0,sizeof(t_wasm));
    // init_all(wasm);
        if (init_all(wasm) != 0)
    {
        // Handle initialization error
        delete wasm; // Clean up allocated memory
        return 1;
    }


    // const int targetFPS = 60;


    // std::vector<std::vector<char> > themap;
// emscripten_set_main_loop(wasm_loop(window), targetFPS, 1);
emscripten_set_main_loop_arg(wasm_loop,wasm,wasm->targetFPS,1);
    // SDL_DestroyWindow(window);
    // SDL_Quit();

    return 0;
}