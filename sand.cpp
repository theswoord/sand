#include "sand.hpp"

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

void update_position_neo(std::vector<std::vector<char> > &thesand)
{
        int logicalW = WWIDTH / sandsize;
    int logicalH = WHEIGHT / sandsize;
    
    for (int y = logicalH - 1; y >= 0; --y)
    {
        for (int x = logicalW - 1; x >= 0; --x) 
        {
            if (thesand[y][x] == SAND)
            {

                if (y + 1 < logicalH && thesand[y+1][x] == EMPTY)
                {
                    thesand[y+1][x] = SAND;
                    thesand[y][x] = EMPTY;
                }
                else if (y + 1 < logicalH)
                {
                     bool canMoveLeft = (x - 1 >= 0 && thesand[y+1][x-1] == EMPTY);
                    bool canMoveRight = (x + 1 < logicalW && thesand[y+1][x+1] == EMPTY);
                     
                if(canMoveRight)
                {
                        thesand[y+1][x+1] = SAND;
                        thesand[y][x] = EMPTY;
                }
                else if(canMoveLeft)
                {
                        thesand[y+1][x-1] = SAND;
                        thesand[y][x] = EMPTY;
                }
                }
                // if(y + 1 < logicalH && thesand[y+1][x] == SAND)
                // {
                //     if (y + 1 < logicalH && thesand[y+1][x+1] == EMPTY)
                //     {
                //             thesand[y+1][x+1] = SAND;
                //             thesand[y][x] = EMPTY;
                //     }
                //      if(x > 0 && y + 1 < logicalH && thesand[y+1][x-1] == EMPTY)
                //     {
                //         thesand[y+1][x-1] = SAND;
                //             thesand[y][x] = EMPTY;
                //     }
                // }
            }
        }
    }
}

Uint32 rand_sand_color()
{

static std::random_device rd; // Obtain a seed from the hardware
static std::mt19937 gen(rd()); // Seed the generator


    Uint32 select = 0;


    // int rnd = gen() %3 ;
    // if(rnd == 1)
    // select =  0xFF << 24| 0xC2 <<16 | 0xB2 << 8 | 0x80;
    // if(rnd == 2)
    // select =  0xFF << 24| 0xE2 <<16 | 0xCA << 8 | 0x76;
    // if(rnd == 3)
    select =  0xFF << 24| 0xCB <<16 | 0xBD << 8 | 0x93;


    return(select);
}

void show_sand_neo(SDL_Surface *screen, SDL_Rect *rec, std::vector<std::vector<char> > &thesand)
{

    int logicalW = WWIDTH / sandsize;
    int logicalH = WHEIGHT / sandsize;


for (int y = logicalH - 1; y >= 0; --y)
    {
        for (int x = logicalW - 1; x >= 0; --x) 
        {
            if (thesand[y][x] == SAND)
            {
                rec->x = x * sandsize;
                rec->y = y * sandsize;
                rec->w = sandsize;
                rec->h = sandsize;
                // SDL_FillRect(screen, rec, SDL_MapRGB(screen->format, 0xC2, 0xB2, 0x80));
                // SDL_FillRect(screen, rec,  4290949760);
                SDL_FillRect(screen, rec, rand_sand_color() );
                // std::cout << SDL_MapRGB(screen->format, 0xC2, 0xB2, 0x80) << std::endl ;

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
// bool sand::Get_move_status()
// {
//     return this->can_move;
// }