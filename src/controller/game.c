#include <MLV/MLV_all.h>
#include <MLV/MLV_time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/enemies_controller.h"
#include "../include/player_controller.h"
#include "../include/key_listener.h"

Game *create_game()
{

    Game *game = malloc(sizeof(Game));
    assert(game != NULL);

    game->player = malloc(sizeof(Player));
    assert(game->player != NULL);

    
    Player *player = init_player();
    init_tab_enemy(game->tab_enemy);
    init_tab_rocket(game->tab_rocket);

   
    game->player = player;

    game->scale = 0;
    game->number_enemies_key = 0;
    game->number_rocket_key = 0;
    game->end_game = 0;

    return game;
}