/**
 * @file powerup.c
 * @brief It's the controller of the powerup
 * @details This file contains all the functions that manage the powerup of the game
 * @author Nicolas Ainouz
 * @version 1.0
 * @date 08/06/2022
 */

#include <MLV/MLV_all.h>
#include <math.h>
#include <assert.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/window.h"

/**
 * @brief Create a powerup object
 * 
 * @param game 
 */
void create_powerup(Game *game)
{
    int x = rand() % NB_POWER_UP + 1;

    game->powerup->in_the_game = 1;
    game->powerup->type = x;
    game->powerup->speed = 5;
    Position *position = malloc(sizeof(Position));
    assert(position != NULL);
    position->x = WIDTH_FRAME;
    position->y = rand() % (HEIGHT_FRAME - SIZE_POWER_UP);
    if (position->y < PADDING_TOP)
    {
        int x = PADDING_TOP - position->y;
        position->y += x;
    }
    game->powerup->position = position;
}

/**
 * @brief Function that check if the player touch the powerup
 * 
 * @param game the game structure
 * @return int the boolean if the player touch the powerup
 */
int touch_powerup(Game *game)
{
    if (game->powerup->position->x < game->player->position->x + game->player->size &&
        game->powerup->position->x + SIZE_POWER_UP > game->player->position->x &&
        game->powerup->position->y < game->player->position->y + game->player->size &&
        game->powerup->position->y + SIZE_POWER_UP > game->player->position->y)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Function that give the powerup to the player
 * 
 * @param game the game structure
 */
void player_get_powerup(Game *game)
{
    if (touch_powerup(game))
    {
        game->powerup->in_the_game = 0;
        game->player->has_powerup = 1;
        free(game->powerup->position);
        game->powerup->position = NULL;
        game->player->powerup->type = game->powerup->type;
        game->player->powerup->animation = 10000;
    }
}

/**
 * @brief Function that move the powerup
 * 
 * @param game is the game structure
 */
void move_powerup(Game *game)
{
    if (game->powerup->position->x < 0 - SIZE_POWER_UP)
    {
        game->powerup->in_the_game = 0;
        free(game->powerup->position);
    }
    else
    {
        game->powerup->position->x -= game->powerup->speed;
        player_get_powerup(game);
    }
    
}
