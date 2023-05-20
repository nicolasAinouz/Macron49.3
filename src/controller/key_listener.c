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
    if (bool == 0)
    {
        inertie(game);
        return;
    }
    game->player->speed = game->player->powerup->is_actif && game->player->powerup->type == 3 ? 40 : 20;
}

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

void space(Game *game)
{
    if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED)
    {
        shoot(game, NULL, 0, 1);
    }
}
void shift(Game *game)
{
    if (MLV_get_keyboard_state(MLV_KEYBOARD_LSHIFT) == MLV_PRESSED && game->player->powerup->type > 0)
    {
        if (game->player->has_powerup == 1)
        {
            active_power_up(game);
        }
    }
}
void escape(Game *game)
{
    if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED)
    {
        game->end_game = 1;
    }
}
void key_listener(Game *game)
{
    move_player(game);

    apply_inertie(game);

    space(game);
    shift(game);
    escape(game);
}
