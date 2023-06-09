/**
 * @file enemies_controller.c
 * @brief It's the controller of the enemies
 * @details This file contains all the functions that manage the enemies of the game
 * @author Nicolas Ainouz
 * @version 1.0
 * @date 08/06/2022
 */

#include <MLV/MLV_all.h>
#include <math.h>
#include <stdlib.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/key_listener.h"
#include "../include/player_controller.h"
#include "../include/window.h"
#include "../include/game.h"
#include "../include/rocket_controller.h"

/**
 * @brief Function who init all the enemies of the game
 *
 * @param tab_enemy the tab of the enemies
 */
void init_tab_enemy(Enemy **tab_enemy)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        Enemy *enemy = malloc(sizeof(Enemy));
        assert(enemy != NULL);
        Position *position = malloc(sizeof(Position));
        assert(position != NULL);

        Hitbox *hitbox = malloc(sizeof(Hitbox));
        assert(hitbox != NULL);
        Position *position_hitbox = malloc(sizeof(Position));
        assert(position_hitbox != NULL);

        hitbox->position = position_hitbox;
        enemy->hitbox = hitbox;

        enemy->position = position;

        tab_enemy[i] = enemy;
    }
}

/**
 * @brief Function that check if the rocket touch the enemy
 *
 * @param rocket rocket structure
 * @param enemy enemy structure
 * @return int boolean if the rocket touch the enemy
 */
int is_inside_hitbox(Rocket *rocket, Enemy *enemy)
{
    if (rocket->hitbox->position->x + rocket->hitbox->size > enemy->hitbox->position->x && rocket->hitbox->position->x < enemy->hitbox->position->x + enemy->hitbox->size && rocket->hitbox->position->y + rocket->hitbox->size > enemy->hitbox->position->y && rocket->hitbox->position->y < enemy->hitbox->position->y + enemy->hitbox->size)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Function that manage the shoot of the enemies
 *
 * @param game the game structure
 */
void enemy_shoot(Game *game)
{

    for (int i = 0; i < NUMBER_OF_ENEMY ;i++)
    {
        if (normal_delay(1) < 0.010 && game->tab_enemy[i]->is_alive && !game->tab_enemy[i]->is_special)
        {
            shoot(game, game->tab_enemy[i], 0, 0);
        }
        else if (normal_delay(1) < 0.01 && game->tab_enemy[i]->is_alive && game->tab_enemy[i]->is_special)
        {
            shoot(game, game->tab_enemy[i], 1, 0);
        }
    }
}

/**
 * @brief Function that check if the rocket touch the enemy
 *
 * @param game the game structure
 */
void touch_by_rocket(Game *game)
{
    rocket_available(game);
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        for (int j = 0; j < NUMBER_OF_ROCKET; j++)
        {

            if (game->tab_rocket[j]->is_alive && game->tab_enemy[i]->is_alive && is_inside_hitbox(game->tab_rocket[j], game->tab_enemy[i]) && game->tab_rocket[j]->is_player)
            {
                game->tab_rocket[j]->is_alive = 0;

                game->tab_enemy[i]->health -= game->tab_rocket[j]->damage;

                if (game->tab_enemy[i]->health <= 0)
                {

                    game->tab_enemy[i]->is_alive = 0;
                }
            }
        }
    }
}

/**
 * @brief Function that move the enemies
 *
 * @param game the game structure
 */
void move(Game *game)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        game->tab_enemy[i]->position->x -= game->tab_enemy[i]->speed;
        Hitbox *hitbox = malloc(sizeof(Hitbox));
        hitbox->position = game->tab_enemy[i]->position;
        hitbox->size = game->tab_enemy[i]->size;
        game->tab_enemy[i]->hitbox = hitbox;
    }
}

/**
 * @brief Function that check if the special enemy is too close to another special enemy
 *
 * @param game the game structure
 * @return int boolean if the special enemy is too close to another special enemy
 */
int check_distance_enemy(Game *game)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        if (game->tab_enemy[i]->is_special && game->tab_enemy[i]->hitbox->position->x < WIDTH_FRAME + SIZE_ENEMY && game->tab_enemy[i]->hitbox->position->x > WIDTH_FRAME - SIZE_ENEMY * 3)
        {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Function that give the index of the first available enemy
 *
 * @param game the game structure
 */
int get_available_enemy(Game *game)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        if (!game->tab_enemy[i]->is_alive)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Create a enemy object
 *
 * @param game the game structure
 * @param is_special the boolean if the enemy is special
 */
void create_enemy(Game *game, int is_special)
{
    if (is_special && !check_distance_enemy(game))
    {
        return;
    }
    int index = get_available_enemy(game);
    Enemy *enemy = game->tab_enemy[index];

    switch (is_special)
    {
    case 0:
        enemy->size = SIZE_ENEMY;
        enemy->position->x = WIDTH_FRAME + SIZE_ENEMY;
        enemy->position->y = rand() % (HEIGHT_FRAME - (SIZE_ENEMY * 2));
        if (enemy->position->y < PADDING_TOP)
        {
            int x = PADDING_TOP - enemy->position->y;
            enemy->position->y += x;
        }
        enemy->health = HEALTH_ENEMY;
        enemy->speed = SPEED_ENEMY;
        enemy->is_special = 0;
        break;
    case 1:
        enemy->size = SIZE_ENEMY_TANK;
        enemy->position->x = WIDTH_FRAME;
        enemy->position->y = HEIGHT_FRAME - enemy->size;
        enemy->health = HEALTH_SPECIAL_ENEMY;
        enemy->speed = SPEED_SPECIAL_ENEMY;
        enemy->is_special = 1;

        break;
    default:
        break;
    }

    enemy->hitbox->position = enemy->position;
    enemy->hitbox->size = enemy->size;

    enemy->is_alive = 1;
    game->tab_enemy[index] = enemy;
}

/**
 * @brief Function that check if the enemy is available (if he is out of the screen, if he is dead)
 *
 * @param game the game structure
 */
void enemies_available(Game *game)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {

        if (game->tab_enemy[i]->position->x < 0 - game->tab_enemy[i]->size)
        {
            if (game->tab_enemy[i]->is_alive)
            {
                game->player->health -= 1;
                game->tab_enemy[i]->is_alive = 0;
            }
        }
    }
}

/**
 * @brief Function that check if the enemy touch the player
 *
 * @param enemy the enemy structure
 * @param player the player structure
 * @return int boolean if the enemy touch the player
 */
int is_inside_player_hitbox(Enemy *enemy, Player *player)
{
    if (enemy->hitbox->position->x < player->hitbox->position->x + player->hitbox->size && enemy->hitbox->position->x + enemy->hitbox->size > player->hitbox->position->x && enemy->hitbox->position->y < player->hitbox->position->y + player->hitbox->size && enemy->hitbox->position->y + enemy->hitbox->size > player->hitbox->position->y)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Function that check if the enemy is inside the ulti hitbox
 *
 * @param enemy the enemy structure
 * @param player the player structure
 * @return int boolean if the enemy is inside the ulti hitbox
 */
int is_inside_ulti_hitbox(Enemy *enemy, Player *player)
{
    if (enemy->hitbox->position->x < player->hitbox->position->x + player->hitbox->size + 900 && enemy->hitbox->position->x + enemy->hitbox->size > player->hitbox->position->x + 90 && enemy->hitbox->position->y < player->hitbox->position->y + player->hitbox->size + 100 && enemy->hitbox->position->y + enemy->hitbox->size > player->hitbox->position->y - 100)
    {

        return 1;
    }
    return 0;
}

/**
 * @brief Function that check if the enemy touch the player and kill him
 *
 * @param game the game structure
 */
void enemy_touch_player(Game *game)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        if (game->tab_enemy[i]->is_alive && is_inside_player_hitbox(game->tab_enemy[i], game->player))
        {
            if (!(game->player->powerup->is_actif && game->player->powerup->type == 1))
            {
                game->tab_enemy[i]->is_alive = 0;
                game->player->health -= 1;
            }
        }
    }
}

/**
 * @brief Function that check if the enemy is inside the ulti hitbox and kill him
 *
 * @param game the game structure
 */
void touch_by_ultime(Game *game)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        if (game->tab_enemy[i]->is_alive && is_inside_ulti_hitbox(game->tab_enemy[i], game->player) && game->player->powerup->is_actif && game->player->powerup->type == 1 && game->player->powerup->animation < 70)
        {
            game->tab_enemy[i]->is_alive = 0;
        }
    }
}

/**
 * @brief Function that draw the enemy
 *
 * @param game the game structure
 */
void call_view(Game *game)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {

        if (game->tab_enemy[i]->is_alive)
        {
            game->tab_enemy[i]->is_special ? draw_enemy(game->tab_enemy[i], game->image->img_enemy_tank), draw_enemy_health(game->tab_enemy[i]) : draw_enemy(game->tab_enemy[i], game->image->img_enemy);
        }
    }
}

/**
 * @brief Function that manage the enemies
 *
 * @param game
 */
void move_enemies(Game *game)
{
    if (normal_delay(30) < 0.5 * game->difficulty)
        create_enemy(game, 0);

    if (normal_delay(30) < 0.3 * game->difficulty)
        create_enemy(game, 1);

    enemies_available(game);
    touch_by_rocket(game);
    touch_by_ultime(game);
    move(game);
    enemy_shoot(game);
    enemy_touch_player(game);

    call_view(game);
}
