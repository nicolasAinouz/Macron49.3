/**
 * @file rocket_controller.c
 * @brief rocket controller file
 * @details This file contains all the functions that manage the rocket of the game
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

/**
 * @brief Function who init all the rocket of the game
 *
 * @param tab_rocket
 */
void init_tab_rocket(Rocket **tab_rocket)
{
    for (int i = 0; i < NUMBER_OF_ROCKET; i++)
    {
        Rocket *rocket = malloc(sizeof(Rocket));
        assert(rocket != NULL);
        Position *position = malloc(sizeof(Position));
        assert(position != NULL);
        position->x = 0;
        position->y = 0;
        rocket->position = position;
        rocket->size = 0;
        rocket->speed = 0;
        rocket->damage = 0;
        rocket->is_alive = 0;
        rocket->is_player = 0;

        Hitbox *hitbox = malloc(sizeof(Hitbox));
        assert(hitbox != NULL);
        Position *position_hitbox = malloc(sizeof(Position));
        assert(position_hitbox != NULL);
        hitbox->position = position_hitbox;
        rocket->hitbox = hitbox;
        rocket->position->x = 0;
        rocket->position->y = 0;
        rocket->hitbox->position->x = 0;
        rocket->hitbox->position->y = 0;
        rocket->hitbox->size = 0;
        rocket->size = 0;
        rocket->speed = 0;
        rocket->damage = 0;
        rocket->is_alive = 0;
        rocket->is_player = 0;
        rocket->is_special = 0;
        tab_rocket[i] = rocket;
    }
}

/**
 * @brief Function that manage the explosion animation
 *
 * @param game the game structure
 * @param i the index of the rocket
 */
void special_rocket_explosing(Game *game, int i)
{
    game->tab_rocket[i]->damage = 0;
    draw_explosion(game->tab_rocket[i]->position->x, game->tab_rocket[i]->position->y, game->image->img_explosion);
    game->tab_rocket[i]->time_explosion--;
}

/**
 * @brief Function that kill the special rocket after the explosion
 *
 * @param game the game structure
 * @param i the index of the rocket
 */
void kill_special_rocket(Game *game, int i)
{
    game->tab_rocket[i]->is_alive = 0;
}

/**
 * @brief Function that move the special rocket for they follow the player
 *
 * @param game the game structure
 * @param i the index of the rocket
 */
void move_special_rocket(Game *game, int i)
{
    float dx = (float)(game->player->position->x - game->tab_rocket[i]->position->x);
    float dy = (float)(game->player->position->y - game->tab_rocket[i]->position->y);
    float length = sqrt(dx * dx + dy * dy);
    float dirx = dx / length;
    float diry = dy / length;

    float move_x = dirx * game->tab_rocket[i]->speed;
    float move_y = diry * game->tab_rocket[i]->speed;

    game->tab_rocket[i]->position->x += move_x;
    game->tab_rocket[i]->position->y += move_y;
}

/**
 * @brief Function that update the special rocket : manage the explosion, the movement and the death
 *
 * @param game the game structure
 * @param i the index of the rocket
 */
void update_special_rocket(Game *game, int i)
{
    game->tab_rocket[i]->time -= 1;
    if (game->tab_rocket[i]->time < 0 && game->tab_rocket[i]->time_explosion > 0)
    {
        special_rocket_explosing(game, i);
    }
    else if (!game->tab_rocket[i]->time_explosion)
    {
        kill_special_rocket(game, i);
    }
    else
    {
        move_special_rocket(game, i);
    }
}

/**
 * @brief Function that move the rocket of the player
 *
 * @param game the game structure
 * @param i the index of the rocket
 */
void move_rocket_player(Game *game, int i)
{
    game->tab_rocket[i]->position->x += game->tab_rocket[i]->speed;
}

/**
 * @brief Function that move the rocket of the enemy
 *
 * @param game the game structure
 * @param i the index of the rocket
 */
void move_rocket_enemy(Game *game, int i)
{
    game->tab_rocket[i]->position->x -= game->tab_rocket[i]->speed;
}

/**
 * @brief Function that manage the movement of the rocket and draw it
 *
 * @param game the game structure
 */
void move_rocket(Game *game)
{
    for (int i = 0; i < NUMBER_OF_ROCKET; i++)
    {
        game->tab_rocket[i]->is_player ? move_rocket_player(game, i) : game->tab_rocket[i]->is_special ? update_special_rocket(game, i)
                                                                                                       : move_rocket_enemy(game, i);

        if (game->tab_rocket[i]->is_player)
            draw_rocket(game->tab_rocket[i], game->image->img_bullet_player);
        else
        {
            if (game->tab_rocket[i]->is_special && game->tab_rocket[i]->time > 0)
            {
                draw_rocket(game->tab_rocket[i], game->image->img_bullet_tank);
            }
            else if (!game->tab_rocket[i]->is_special)
            {
                draw_rocket(game->tab_rocket[i], game->image->img_bullet_tank);
            }
        }
    }
}

/**
 * @brief Function that check if the rocket touch the player
 *
 * @param rocket the rocket
 * @param player the player
 * @return int boolean if the rocket touch the player
 */
int rocket_touch_player(Rocket *rocket, Player *player)
{

    if (!rocket->is_player)
    {

        if (rocket->hitbox->position->x + rocket->hitbox->size > player->position->x && rocket->hitbox->position->x < player->position->x + player->size && rocket->hitbox->position->y + rocket->hitbox->size > player->position->y && rocket->hitbox->position->y < player->position->y + player->size)
        {
            if (!(player->powerup->is_actif && player->powerup->type == 1))
                return 1;
        }
    }
    return 0;
}

/**
 * @brief Function that check if the rocket is out of the map
 *
 * @param rocket the rocket
 * @param game the game structure
 * @return int the boolean if the rocket is out of the map
 */
int is_out_of_map(Rocket *rocket, Game *game)
{
    if (rocket->position->x < 0 + rocket->size || rocket->position->x > WIDTH_FRAME)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Function that update the tab of rocket -> delete the rocket
 *
 * @param game game structure
 * @param i the index of the rocket
 */
void update_tab_rocket(Game *game, int i)
{
    Rocket *rocket = game->tab_rocket[i];
    rocket->position->x = 0;
    rocket->position->y = 0;
    rocket->hitbox->position->x = 0;
    rocket->hitbox->position->y = 0;
    rocket->hitbox->size = 0;
    rocket->size = 0;
    rocket->speed = 0;
    rocket->damage = 0;
    rocket->is_alive = 0;
    rocket->is_player = 0;
    rocket->is_special = 0;
}

/**
 * @brief Function that check if the rocket respect all the condition
 *
 * @param game the game structure
 */
void rocket_available(Game *game)
{
    for (int i = 0; i < NUMBER_OF_ROCKET; i++)
    {
        if (is_out_of_map(game->tab_rocket[i], game))
        {
            update_tab_rocket(game, i);
        }

        if (rocket_touch_player(game->tab_rocket[i], game->player))
        {
            game->player->health -= game->tab_rocket[i]->damage;

            update_tab_rocket(game, i);
        }
        if (!game->tab_rocket[i]->is_alive)
        {
            update_tab_rocket(game, i);
        }
    }
}

/**
 * @brief Function that return the index of the first available rocket
 *
 * @param game the game structure
 * @return int the index of the first available rocket
 */
int get_available_rocket(Game *game)
{
    for (int i = 0; i < NUMBER_OF_ROCKET; i++)
    {
        if (!game->tab_rocket[i]->is_alive)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Function for shoot a rocket for player and enemy
 *
 * @param game the game structure
 * @param enemy the enemy who shoot
 * @param is_special boolean if the ennemy is special
 * @param is_player boolean if the rocket is shoot by the player
 */
void shoot(Game *game, Enemy *enemy, int is_special, int is_player)
{
    int index = get_available_rocket(game);
    Rocket *rocket = game->tab_rocket[index];

    switch (is_player)
    {
    case 1:

        rocket->position->x = game->player->position->x + game->player->size;
        rocket->position->y = game->player->position->y;

        rocket->size = ROCKET_SIZE;

        rocket->hitbox->position = rocket->position;
        rocket->hitbox->size = rocket->size;

        rocket->speed = 30;
        rocket->damage = 5;

        rocket->is_alive = 1;
        rocket->is_player = 1;

        break;
    case 0:
        switch (is_special)
        {
        case 0:
            rocket->position->y = enemy->position->y + SIZE_ENEMY / 2;
            rocket->speed = 15;
            break;
        case 1:
            rocket->position->y = enemy->position->y + SIZE_ENEMY_TANK / 2.2;
            rocket->speed = 5;
            rocket->time = 200;
            rocket->time_explosion = TIME_EXPLOSION_SPECIAL_ROCKET;

            break;
        default:
            break;
        }
        rocket->position->x = enemy->position->x;
        rocket->size = ROCKET_ENNEMY_SIZE;
        rocket->damage = 1;
        rocket->is_alive = 1;
        rocket->is_player = 0;
        rocket->is_special = is_special;
        rocket->hitbox->position = rocket->position;
        rocket->hitbox->size = rocket->size;

        break;
    default:
        break;
    }
    game->tab_rocket[index] = rocket;
}
