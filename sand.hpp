#include <iostream>
// #include "/goinfre/nbouhali/homebrew/include/SDL2/SDL.h"
#include "./SDL/include/SDL.h"
#include <emscripten.h>

#include <unistd.h>
#include <vector>
#include <random>
#include <string>
#define Velocity 3
#define WWIDTH 800
#define WHEIGHT 600
#define sandsize 3
#define UP 8
#define DOWN 2
#define LEFT 4
#define RIGHT 6
#define EMPTY 0
#define SAND 1
#define WATER 2
#define ROCK 3
#define LADY 4
#define WETSAND 5
#define ZINJAR 6
#define SPONGE 7




// std::random_device rd; // Obtain a seed from the hardware
// std::mt19937 gen(rd());



class sand
{
    private:
    int x;
    int y;
    bool alive;
    bool can_move;
    public:
    sand(int _x, int _y);
    bool Get_alive_status();
    // bool Get_move_status();

    void Set_alive_status(bool what);
    void increment_x();
    void increment_y();

    bool check_everytime();


    int get_x_value();
    int get_y_value();
};

void random_sand_gen(std::vector<std::vector<char> > &thesand);
void show_sand(SDL_Surface *screen ,SDL_Rect *rec ,std::vector<sand> &thesand);
void show_sand_neo(SDL_Surface *screen ,SDL_Rect *rec ,std::vector< std::vector<char> > &thesand);

void update_gravity(std::vector<sand> &thesand);

void update_position_neo(std::vector<std::vector<char> > &thesand);

// bool check_collision(sand &sand);