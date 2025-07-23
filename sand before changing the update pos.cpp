#include "sand.hpp"

void random_sand_gen(std::vector<std::vector<char>> &thesand)
{

    static std::random_device rd;  // Obtain a seed from the hardware
    static std::mt19937 gen(rd()); // Seed the generator

    int x = gen() % WWIDTH;
    int y = gen() % WHEIGHT;

    int picker = gen() % 4 + 1;

    // printf("i picked %d \n", picker);

    int logicalX = x / sandsize;
    int logicalY = y / sandsize;

    int logicalW = WWIDTH / sandsize;
    int logicalH = WHEIGHT / sandsize;

    if (logicalY >= 0 && logicalY < logicalH - 5 && logicalX >= 0 && logicalX < logicalW)
    {
        if (thesand[logicalY + 4][logicalX] == EMPTY)
        { // andzid ngad had randomizer ban lia 3yan hehe
            thesand[logicalY][logicalX] = picker;
            thesand[logicalY + 1][logicalX] = picker;
            thesand[logicalY + 2][logicalX] = picker;
            thesand[logicalY + 3][logicalX] = picker;
            thesand[logicalY + 4][logicalX] = picker;
        }
        // thesand[logicalY+1][logicalX+1] = SAND;
        // thesand[logicalY-1][logicalX-1] = SAND;
    }
}

void show_sand(SDL_Surface *screen, SDL_Rect *rec, std::vector<sand> &thesand)
{

    std::vector<sand>::iterator it = thesand.begin();
    // std::cout << thesand.size() << std::endl;
    while (it != thesand.end())
    {
        rec->x = it->get_x_value();
        rec->y = it->get_y_value();

        // std::cout << "hh " << rec->x <<  " " << rec->y << std::endl;
        SDL_FillRect(screen, rec, SDL_MapRGB(screen->format, 0xFF, 0xB2, 0x80));

        it++;
        /* code */
    }
}

void specific_element(std::vector<std::vector<char>> &thesand, int *y, int *x, int what)
{
    int logicalW = WWIDTH / sandsize;
    int logicalH = WHEIGHT / sandsize;
    static std::random_device rd;  // Obtain a seed from the hardware
    static std::mt19937 gen(rd()); // Seed the generator
    if (what == SAND)
    {
        if (*y + 1 < logicalH && thesand[*y + 1][*x] == EMPTY)
        {
            thesand[*y + 1][*x] = what;
            thesand[*y][*x] = EMPTY;
        }
        else if (*y + 1 < logicalH)
        {
            bool canMoveLeft = (*x - 1 >= 0 && thesand[*y + 1][*x - 1] == EMPTY);
            bool canMoveRight = (*x + 1 < logicalW && thesand[*y + 1][*x + 1] == EMPTY);

            if (canMoveRight)
            {
                thesand[*y + 1][*x + 1] = what;
                thesand[*y][*x] = EMPTY;
            }
            else if (canMoveLeft)
            {
                thesand[*y + 1][*x - 1] = what;
                thesand[*y][*x] = EMPTY;
            }
        }
    }
    if (what == ROCK)
    {
        if (*y + 1 < logicalH && thesand[*y + 1][*x] == EMPTY)
        {
            thesand[*y + 1][*x] = what;
            thesand[*y][*x] = EMPTY;
        }
    }
    // if (what == ACID)
    // {
    //     int dir = (gen() % 2) * 2 - 1;
    //     // printf("%d \n", dir);
    //     if (*y + 1 < logicalH && thesand[*y + 1][*x] == EMPTY)
    //     {
    //         thesand[*y + 1][*x] = what;
    //         thesand[*y][*x] = EMPTY;
    //         return ;
    //     }
    //     if( *x - 1 >= 0 && *x + 1 < logicalW && thesand[*y ][*x+1] == EMPTY || thesand[*y ][*x-1] == EMPTY  )
    //     {

    //         thesand[*y][*x + dir] = what;
    //         thesand[*y][*x] = EMPTY;
    //     }
    // }
    if (what == WATER)
    {
        // int dir = (gen() % 2) * 2 - 1;
        static int direction = 1;
        // printf("%d \n", dir);
        if (*y + 1 < logicalH && thesand[*y + 1][*x] == EMPTY)
        {
            thesand[*y + 1][*x] = what;
            thesand[*y][*x] = EMPTY;
            return;
        }
    if (*x + direction >= logicalW || *x + direction < 0 || thesand[*y][*x + direction] != EMPTY)
    {
        direction *= -1;
    }
    if (*x + direction < logicalW && *x + direction >= 0 && thesand[*y][*x + direction] == EMPTY)
    {
        thesand[*y][*x + direction] = what;
        thesand[*y][*x] = EMPTY;
        return;
    }
    }
}

void update_position_neo(std::vector<std::vector<char>> &thesand)
{
    int logicalW = WWIDTH / sandsize;
    int logicalH = WHEIGHT / sandsize;

    for (int y = logicalH - 1; y >= 0; --y)
    {
        for (int x = logicalW - 1; x >= 0; --x)
        {
            if (thesand[y][x] != EMPTY)
            {
                int what = thesand[y][x];
                specific_element(thesand, &y, &x, what);
            }
        }
    }
}

Uint32 rand_sand_color()
{

    static std::random_device rd;  // Obtain a seed from the hardware
    static std::mt19937 gen(rd()); // Seed the generator

    Uint32 select = 0;

    // int rnd = gen() %3 ;
    // if(rnd == 1)
    // select =  0xFF << 24| 0xC2 <<16 | 0xB2 << 8 | 0x80;
    // if(rnd == 2)
    // select =  0xFF << 24| 0xE2 <<16 | 0xCA << 8 | 0x76;
    // if(rnd == 3)
    select = 0xFF << 24 | 0xCB << 16 | 0xBD << 8 | 0x93;

    return (select);
}

void show_sand_neo(SDL_Surface *screen, SDL_Rect *rec, std::vector<std::vector<char>> &thesand)
{

    int logicalW = WWIDTH / sandsize;
    int logicalH = WHEIGHT / sandsize;

    for (int y = logicalH - 1; y >= 0; --y)
    {
        for (int x = logicalW - 1; x >= 0; --x)
        {
            rec->x = x * sandsize;
            rec->y = y * sandsize;
            rec->w = sandsize;
            rec->h = sandsize;
            if (thesand[y][x] == SAND)
            {
                SDL_FillRect(screen, rec, SDL_MapRGB(screen->format, 0xF2, 0xD2, 0xA9)); // f2d2a9
            }
            if (thesand[y][x] == WATER)
            {
                SDL_FillRect(screen, rec, SDL_MapRGB(screen->format, 0x99, 0xC0, 0xE3)); // f2d2a9
            }
            if (thesand[y][x] == ROCK)
            {
                SDL_FillRect(screen, rec, SDL_MapRGB(screen->format, 0x7F, 0x83, 0x86)); // f2d2a9
            }
            if (thesand[y][x] == LADY)
            {
                SDL_FillRect(screen, rec, SDL_MapRGB(screen->format, 0xFF, 0xA5, 0x00)); // f2d2a9
            }
        }
    }
}

void update_gravity(std::vector<sand> &thesand)
{
    std::vector<sand>::iterator it = thesand.begin();
    while (it != thesand.end())
    {

        if (it->Get_alive_status() == true)
        {
            if (it->get_y_value() < WHEIGHT - 3)
            {
                it->increment_y();
            }
            // if(it->get_y_value)
        }

        it++;
        /* code */
    }
}

sand::sand(int _x, int _y) : x(_x), y(_y), alive(true)
{
}

int sand::get_x_value()
{
    return this->x;
}
int sand::get_y_value()
{
    return this->y;
}

bool sand::Get_alive_status()
{
    return this->alive;
}

void sand::Set_alive_status(bool what)
{
    this->alive = what;
}

void sand::increment_x()
{
    this->x += Velocity;
}
void sand::increment_y()
{
    this->y += Velocity;
}
