/**
 * @file player_controller.c
 * @brief It's the controller of the player
 * @details This file contains all the functions that manage the player of the game
 * @author Nicolas Ainouz
 * @version 1.0
 * @date 08/06/2022
 */


#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/window.h"

/**
 * @brief Function that init the player
 * 
 * @return Player* 
 */
Player *init_player()
{

    Player *player = malloc(sizeof(Player));
    assert(player != NULL);

    player->size = SIZE_PLAYER;
    Position *position = malloc(sizeof(Position));
    assert(position != NULL);
    position->x = (player->size);
    position->y = HEIGHT_FRAME / 2 - player->size / 2;
    player->position = position;

    player->health = HEALTH_PLAYER;

    Hitbox *hitbox = malloc(sizeof(Hitbox));
    assert(hitbox != NULL);
    hitbox->position = player->position;
    hitbox->size = player->size / 2;
    player->hitbox = hitbox;

    Powerup *powerup = malloc(sizeof(Powerup));
    assert(powerup != NULL);
    player->powerup = powerup;

    return player;
}

/**
 * @brief Function that move the player to the left
 * 
 * @param player the player structure
 */
void move_player_left(Player *player)
{
    if (player->position->x > 0)
    {
        player->position->x = player->position->x - player->speed;
    }
}

/**
 * @brief Function that move the player to the right
 * 
 * @param player player the player structure
 */
void move_player_right(Player *player)
{
    if (player->position->x < WIDTH_FRAME - player->size)
    {
        player->position->x = player->position->x + player->speed;
    }
}

/**
 * @brief Function that move the player to the top
 * 
 * @param player the player structure
 */
void move_player_up(Player *player)
{
    if (player->position->y > PADDING_TOP)
    {
        player->position->y = player->position->y - player->speed;
    }
}

/**
 * @brief Function that move the player to the bottom
 * 
 * @param player the player structure
 */
void move_player_down(Player *player)
{
    if (player->position->y < HEIGHT_FRAME - player->size / 1.1)
    {
        player->position->y = player->position->y + player->speed;
    }
}

/**
 * @brief Function that activate the powerup
 * 
 * @param game the game structure
 */
void active_power_up(Game *game)
{

    switch (game->player->powerup->type)
    {
    case 1:
        game->player->powerup->animation = 180;
        game->player->powerup->is_actif = 1;

        draw_power_up_dbz(game);
        break;
    case 2:
        game->player->powerup->animation = 0;
        game->player->powerup->is_actif = 0;
        game->player->powerup->type = 0;

        if (game->player->health < 5)
        {
            game->player->health += 1;
        }

        break;
    case 3:
        game->player->powerup->animation = 180;
        game->player->powerup->is_actif = 1;
        game->player->powerup->type = 3;
        game->player->speed = 80;
        break;
    default:
        break;
    }

    game->player->has_powerup = 0;
}

/**
 * @brief Function who check if the player is dead
 * 
 * @param game the game structure
 * @return int boolean if the player is dead
 */
int player_is_dead(Game *game)
{
    return game->player->health <= 0 ? 1 : 0;
}

/**
 * @brief Function that check if the player is shooting too much
 * 
 * @param game the game structure
 */
void check_shooting_to_much(Game *game)
{
    if (game->player->is_shooting_too_much && game->player->shoot <= 0)
    {
        game->player->is_shooting_too_much = 0;
    }
    else if (game->player->shoot >= 100)
    {
        game->player->is_shooting_too_much = 1;
    }
    if (game->player->shoot > -1)
        game->player->shoot -= 2;

    draw_shoot_bar(game);
}

/**
 * @brief Function that manage the player and draw it
 * 
 * @param game the game structure
 */
void player_update(Game *game)
{
    check_shooting_to_much(game);
    draw_player(game);
    draw_health(game);
    draw_score(game);
}