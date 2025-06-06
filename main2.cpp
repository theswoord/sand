#include "sand.hpp"

int main()
{
    int a = 4;

    a = 1;

    std::cout << a << std::endl;
    SDL_Event event;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    // SDL_rect *rectangle;
    SDL_Rect rectangle;
    rectangle.h = 50;
    rectangle.w = 25;
    rectangle.x = 300;
    rectangle.y = 300;

    // SDL_memset()
    // memset()

    SDL_Surface *screenSurface = NULL;

    window = SDL_CreateWindow("miw", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

    // SDL_Delay(2000);

    // Get window surface
    screenSurface = SDL_GetWindowSurface(window);

    // Fill the surface white
    SDL_FillRect(screenSurface, &rectangle, SDL_MapRGB(screenSurface->format, 120, 0x2, 0x11));

    // Update the surface
    // while (1)
    // {
    //     SDL_UpdateWindowSurface(window);
    //     rectangle.h += 3;
    //     rectangle.w += 1;
    //     if (rectangle.h >= 111 || rectangle.w >= 111)
    //     {
    //         rectangle.h = 11;
    //         rectangle.w = 69;
    //     }
    // }
    // srand(time_t(NULL) );
    // int i = 0;
    // int i
    // rand()%10 =

    // Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            SDL_UpdateWindowSurface(window);
    SDL_FillRect(screenSurface, &rectangle, SDL_MapRGB(screenSurface->format, 120, 0x2, 0x11));

            rectangle.h += 3;
            rectangle.w += 1;
            if (rectangle.h >= 111 || rectangle.w >= 111)
            {
                rectangle.h = 11;
                rectangle.w = 69;
            }
            if (e.type == SDL_QUIT)
                quit = true;

            usleep(100);
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    // return 0;
}