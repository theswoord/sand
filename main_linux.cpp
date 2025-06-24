#include "sand.hpp"

void clear_window()
{
}

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

int main()
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("miw", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    int x = 0;
    int y = 0;
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    SDL_Rect rectangle = {x, y, 25, 25};
    SDL_Rect particle = {x, y, sandsize, sandsize};

    int mousex = 0;
    int mousey = 0;
    bool quit = false;
    SDL_Event e;

    const int targetFPS = 60;
    const int frameDelay = 1000 / targetFPS; // Milliseconds per frame

    Uint32 frameStart;
    int frameTime;
    bool hold = false;
    std::vector<sand> play;

    std::vector<std::vector<char> > themap;
    init_window(themap);
    // float widthChange = 1.0f;
    // float heightChange = 3.0f;

    while (!quit)
    {
        frameStart = SDL_GetTicks(); // Get the start time of the frame

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                // SDL_GetMouseState(&mousex,&mousey);
                hold = true;
                // printf(x , y)
                x = mousex;
                y = mousey;
                // play.push_back(sand(x,y));
                std::cout << x << " " << y << std::endl;
            }
            if (e.type == SDL_MOUSEBUTTONUP)
            {
                hold = false;
            }
        }
            if (hold)
            {
                SDL_GetMouseState(&mousex, &mousey);
                // x = mousex;
                // y = mousey;
                int logicalX = mousex / sandsize;
                int logicalY = mousey / sandsize;

                int logicalW = WWIDTH / sandsize;
                int logicalH = WHEIGHT / sandsize;

                if (logicalY >= 0 && logicalY < logicalH && logicalX >= 0 && logicalX < logicalW)
                {
                    themap[logicalY][logicalX] = SAND;
                }
            }

        SDL_GetMouseState(&mousex, &mousey);

        rectangle.x = mousex - rectangle.w / 2;
        rectangle.y = mousey - rectangle.h / 2;

        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));

        SDL_FillRect(screenSurface, &rectangle, SDL_MapRGB(screenSurface->format, 0xC2, 0xB2, 0x80));

        // show_sand(screenSurface,&particle,play);
        show_sand_neo(screenSurface, &particle, themap);

        SDL_UpdateWindowSurface(window);
        update_position_neo(themap);
        // update_gravity(play);
        frameTime = SDL_GetTicks() - frameStart;

        // std::cout << play.size() << std::endl;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}