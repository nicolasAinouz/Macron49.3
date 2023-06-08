/**
 * @file key_listener.c
 * @brief It's the keyboard listener of the game
 * @details This file contains all the functions that manage all the keyboard action of the game
 * @author Nicolas Ainouz
 * @version 1.0
 * @date 08/06/2022
 */

#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../include/const.h"
#include "../include/window.h"
#include "../include/struct_entity.h"
#include "../include/player_controller.h"
#include "../include/rocket_controller.h"

/**
 * @brief Function that make inertie to the player
 * 
 * @param game the game structure
 *
 */
void inertie(Game *game)
{
    switch (game->last_keyboard_push)
    {
    case 1:
        move_player_left(game->player);
        break;
    case 2:
        move_player_up(game->player);
        break;
    case 3:

        move_player_right(game->player);
        break;
    case 4:
        move_player_down(game->player);
        break;
    }
}

/**
 * @brief Function that move the player
 * 
 * @param game the game structure
 */
void move_player(Game *game)
{
    int bool = 0;
    if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)
    {
        move_player_left(game->player);
        game->last_keyboard_push = 1;
        bool = 1;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED)
    {
        move_player_up(game->player);
        game->last_keyboard_push = 2;
        bool = 1;
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)
    {
        move_player_right(game->player);
        game->last_keyboard_push = 3;
        bool = 1;
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED)
    {

        move_player_down(game->player);
        game->last_keyboard_push = 4;
        bool = 1;
    }

    if (!bool)
    {
        inertie(game);
        return;
    }
    game->player->speed = game->player->powerup->is_actif && game->player->powerup->type == 3 ? 40 : 20;
}

/**
 * @brief Function that apply the inertie to the player
 * 
 * @param game the game structure
 */
void apply_inertie(Game *game)
{
    if (game->player->speed > 2)
    {
        game->player->speed -= 2;
    }
    else
    {
        game->last_keyboard_push = 0;
    }
}

/**
 * @brief Function that make the player shoot is space is pressed
 * 
 * @param game the game structure
 */
void space(Game *game)
{
    if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED && !game->player->is_shooting_too_much && !(game->player->powerup->type == 1 && game->player->powerup->is_actif))
    {
        shoot(game, NULL, 0, 1);
        game->player->shoot += 10;
    }
}

/**
 * @brief Function that make the player use his powerup if shift is pressed
 * 
 * @param game the game structure
 */
void shift(Game *game)
{
    if (MLV_get_keyboard_state(MLV_KEYBOARD_LSHIFT) == MLV_PRESSED && game->player->powerup->type > 0)
    {
        if (game->player->has_powerup)
        {
            active_power_up(game);
        }
    }
}

/**
 * @brief Function that make the player quit the game if escape is pressed
 * 
 * @param game the game structure
 */
void escape(Game *game)
{
    if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED)
    {
        game->end_game = 1;
    }
}

/**
 * @brief Function that listen the keyboard
 * 
 * @param game the game structure
 */
void key_listener(Game *game)
{
    move_player(game);

    apply_inertie(game);

    space(game);
    shift(game);
    escape(game);
}
