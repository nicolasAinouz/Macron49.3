#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../include/main.h"
#include "../include/const.h"
#include "../include/window.h"
#include "../include/struct_entity.h"
#include "../include/player_controller.h"
#include "../include/rocket_controller.h"

void key_listener(Game *game)
{

    int bool = 0;

    if (game->player->speed > 2)
    {

        game->player->speed -= 2;
    }
    else
    {
        game->last_keyboard_push = 0;
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)
    {
        game->player->speed = 20;
        move_player_left(game->player);
        game->last_keyboard_push = 1;
        bool = 1;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED)
    {
        game->player->speed = 20;
        move_player_up(game->player);
        game->last_keyboard_push = 2;
        bool = 1;
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)
    {
        game->player->speed = 20;
        move_player_right(game->player);
        game->last_keyboard_push = 3;
        bool = 1;
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED)
    {
        game->player->speed = 20;
        move_player_down(game->player);
        game->last_keyboard_push = 4;
        bool = 1;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED)
    {
        shoot(game);
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_LSHIFT) == MLV_PRESSED && game->player->powerup->type > 0)
    {
        if (game->player->has_powerup == 1)
        {
            active_power_up(game);
        }
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED)
    {
        end_game_signal();
    }
    if (bool == 0)
    {
        if (game->last_keyboard_push == 1)
        {

            move_player_left(game->player);
        }
        if (game->last_keyboard_push == 2)
        {
            move_player_up(game->player);
        }
        if (game->last_keyboard_push == 3)
        {
            move_player_right(game->player);
        }
        if (game->last_keyboard_push == 4)
        {
            move_player_down(game->player);
        }
    }

    bool = 1;
}
