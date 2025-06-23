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
void show_sand_neo(SDL_Surface *screen, SDL_Rect *rec, std::vector<std::vector<char>> &thesand)
{

    // std::vector<sand>::iterator it = thesand.begin();
    // std::cout << thesand.size() << std::endl;
    // while (it != thesand.end())
    // {
    //     rec->x = it->get_x_value();
    //     rec->y = it->get_y_value();

    //     // std::cout << "hh " << rec->x <<  " " << rec->y << std::endl;
    //     SDL_FillRect(screen, rec, SDL_MapRGB(screen->format, 0xFF, 0xB2, 0x80));

    //     it++;
    //     /* code */
    // }
    int x, y;
    x = WWIDTH;
    y = WHEIGHT;

    // std::cout << x << " " << y << std::endl;
    while (y >= WHEIGHT)
    {
        /* code */
        x = WWIDTH;
    // std::cout << x << " " << y << std::endl;

        rec->y = y;
        while (x >= WWIDTH)
        {
            /* code */
            std::cout << "miw\n";
            // if (thesand[y][x] == SAND)
            // {
            //     // exit(1);
            rec->x = x;
                SDL_FillRect(screen, rec, SDL_MapRGB(screen->format, 0xFF, 0xB2, 0x80));
            //     /* code */
            // }
            

            x--;
        }

        y--;
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