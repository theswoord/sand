#include "sand.hpp" // Assuming this has SDL includes, WWIDTH, WHEIGHT, sandsize, SAND, EMPTY, etc.

#ifdef __EMSCRIPTEN__
#include <emscripten.h> // Required for emscripten_set_main_loop
#endif

// --- GLOBAL VARIABLES (Accessible across frames) ---
// These need to be accessible by both main() for setup and wasm_loop() for per-frame updates.
SDL_Window *gWindow = nullptr;
SDL_Surface *gScreenSurface = nullptr;
SDL_Rect gRectangle; // Your mouse cursor/tool indicator
SDL_Rect gParticle;  // Used for drawing individual sand particles
std::vector<std::vector<char>> gTheMap; // Your 2D array for sand simulation

SDL_Event gEvent; // Event structure
bool gQuit = false; // Flag to indicate if the game should stop (for native, or internal cleanup for wasm)
bool gHold = false; // Mouse button hold state
int gMouseX = 0;
int gMouseY = 0;

// Frame rate control
const int gTargetFPS = 60;
const int gFrameDelay = 1000 / gTargetFPS; // Milliseconds per frame
Uint32 gFrameStart;
int gFrameTime;

// Assuming these are defined in sand.hpp or globally elsewhere
// extern int WWIDTH;
// extern int WHEIGHT;
// extern int sandsize;
// extern char SAND;
// extern char EMPTY;

// --- Function Prototypes (if not in a header) ---
void show_sand_neo(SDL_Surface *screenSurface, SDL_Rect *particle, const std::vector<std::vector<char>> &themap);
void update_position_neo(std::vector<std::vector<char>> &themap);
void init_window(std::vector<std::vector<char>> &map); // Your existing function

// --- The NEW single-frame game loop function for Emscripten ---
void main_loop_one_frame()
{
    gFrameStart = SDL_GetTicks(); // Get the start time of the frame

    // 1. Process Events
    while (SDL_PollEvent(&gEvent))
    {
        if (gEvent.type == SDL_QUIT)
        {
            gQuit = true; // Signal for potential cleanup or loop exit (more relevant for native)
        }
        if (gEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            gHold = true;
            // No need to get mouse state here; it's updated every frame anyway below
            // But if you need the exact click position, you can use gEvent.button.x/y
        }
        if (gEvent.type == SDL_MOUSEBUTTONUP)
        {
            gHold = false;
        }
    }

    // 2. Update Game State (Input handling, physics, etc.)
    if (gHold)
    {
        SDL_GetMouseState(&gMouseX, &gMouseY); // Get mouse state while held down
        int logicalX = gMouseX / sandsize;
        int logicalY = gMouseY / sandsize;

        int logicalW = WWIDTH / sandsize;
        int logicalH = WHEIGHT / sandsize;

        if (logicalY >= 0 && logicalY < logicalH && logicalX >= 0 && logicalX < logicalW)
        {
            gTheMap[logicalY][logicalX] = SAND; // Place sand
        }
    }

    SDL_GetMouseState(&gMouseX, &gMouseY); // Always update mouse for cursor position
    gRectangle.x = gMouseX - gRectangle.w / 2;
    gRectangle.y = gMouseY - gRectangle.h / 2;

    update_position_neo(gTheMap); // Update sand simulation logic

    // 3. Render
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0)); // Clear screen (black)
    SDL_FillRect(gScreenSurface, &gRectangle, SDL_MapRGB(gScreenSurface->format, 0xC2, 0xB2, 0x80)); // Draw cursor
    show_sand_neo(gScreenSurface, &gParticle, gTheMap); // Draw sand particles
    SDL_UpdateWindowSurface(gWindow); // Present to screen

    // 4. Frame Rate Limiting
    gFrameTime = SDL_GetTicks() - gFrameStart;
    if (gFrameDelay > gFrameTime)
    {
        SDL_Delay(gFrameDelay - gFrameTime); // Delay to maintain target FPS
    }

    // Optional: For Emscripten, if you have a condition to "quit" the game (e.g., game over screen)
    // you would call emscripten_cancel_main_loop(); here and then do any final cleanup.
    // However, usually, a browser game just keeps running until the tab is closed.
    if (gQuit) {
        // emscripten_cancel_main_loop(); // Uncomment if you want to explicitly stop the loop in browser
        // Perform game-specific shutdown logic if any, but SDL_Quit() is often handled by browser tab close.
    }
}

// --- Main function (Initialization) ---
int main(int argc, char* argv[])
{
    // 1. SDL Initialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2. Create Window and Get Surface
    gWindow = SDL_CreateWindow("Sand Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        // std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    gScreenSurface = SDL_GetWindowSurface(gWindow);

    // 3. Initialize Game State Variables
    // Rectangle for cursor
    gRectangle.w = 25; // Assuming your cursor/tool size
    gRectangle.h = 25;
    gRectangle.x = gRectangle.y = 0; // Initial position

    // Particle rectangle (used for drawing individual sand elements)
    gParticle.w = sandsize;
    gParticle.h = sandsize;
    gParticle.x = gParticle.y = 0; // Placeholder, updated in show_sand_neo

    // Initialize the 2D map for sand
    init_window(gTheMap);

#ifdef __EMSCRIPTEN__
    // For Emscripten, set up the main loop to call our single-frame function
    emscripten_set_main_loop(main_loop_one_frame, gTargetFPS, 1);
#else
    // For Native (desktop) builds, keep the traditional while loop
    while (!gQuit)
    {
        // Call the same single-frame logic function
        main_loop_one_frame();
    }
    // Perform SDL cleanup only for native builds (or if emscripten_cancel_main_loop is used)
    SDL_FreeSurface(gScreenSurface);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
#endif

    // Note: The `main` function will exit *after* `emscripten_set_main_loop` is called
    // in the browser environment. The cleanup code below will only be reached in the
    // native build or if `emscripten_cancel_main_loop()` is called.
    return 0;
}

// Your init_window function (from your snippet)
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

// Your wasm_loop function is now effectively renamed and refactored into main_loop_one_frame.
// The `void clear_window()` function seems unused and can be removed unless it serves another purpose.