/**
 * @file game.c
 * @brief It's the controller of the structure game and the utils functions
 * @author Nicolas Ainouz
 * @version 1.0
 * @date 08/06/2022
 */


#include <MLV/MLV_all.h>
#include <MLV/MLV_time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/enemies_controller.h"
#include "../include/player_controller.h"
#include "../include/key_listener.h"
#include "../include/rocket_controller.h"

/**
 * @brief Function that generate random (Function from the Algorithmic course (Thanks Mr Thapper))
 * 
 * @param mean the mean of the random
 * @return double the random
 */
double normal_delay(double mean)
{
    return -mean * log(1 - ((double)rand() / RAND_MAX));
}

/**
 * @brief Initialise the structure of the game who contains all the structure of the game
 * 
 * @return Game* the game structure
 */
Game *create_game()
{

    Game *game = malloc(sizeof(Game));
    assert(game != NULL);

    game->player = malloc(sizeof(Player));
    assert(game->player != NULL);

    Player *player = init_player();

    init_tab_enemy(game->tab_enemy);
    init_tab_rocket(game->tab_rocket);

    Image_Game *image_game = malloc(sizeof(Image_Game));
    assert(image_game != NULL);

    Powerup *powerup = malloc(sizeof(Powerup));
    assert(powerup != NULL);
    game->powerup = powerup;

    game->image = image_game;
    game->player = player;

    game->difficulty = 1;

    return game;
}