#include <MLV/MLV_all.h>
#include <math.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/window.h"

void create_powerup(Game *game)
{
    int x = rand() % NB_POWER_UP;

    game->powerup->is_actif = 1;
    game->powerup->type = x;

    draw_powerup(game);

    
}
