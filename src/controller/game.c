#include <MLV/MLV_all.h>
#include <MLV/MLV_time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "include/const.h"
#include "include/struct_entity.h"
#include "include/enemies_controller.h"
#include "include/player_controller.h"
#include "include/key_listener.h"

Game *create_game()
{

    game *game = malloc(sizeof(Game));
    assert(game != NULL);
    game->tab_enemy = malloc(sizeof(Enemy *) * NUMBER_OF_ENEMY);
    assert(game->tab_enemy != NULL);
    game->tab_rocket = malloc(sizeof(Rocket *) * NUMBER_OF_ROCKET);
    assert(game->tab_rocket != NULL);
    game->player = malloc(sizeof(Player));
    assert(game->player != NULL);

    Enemy *tab_enemy[100];
    Rocket *tab_rocket[100];
    Player *player = init_player();
    init_tab_enemy(tab_enemy);
    init_tab_rocket(tab_rocket);

    game->tab_enemy = tab_enemy;
    game->tab_rocket = tab_rocket;
    game->player = player;

    game->scale = 0;
    game->number_enemies_key = 0;
    game->number_rocket_key = 0;
    game->end_game = 0;

    return game;
}