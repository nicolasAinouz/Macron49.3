#include <MLV/MLV_all.h>
#include <math.h>
#include <stdlib.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/key_listener.h"
#include "../include/player_controller.h"
#include "../include/window.h"

void init_tab_enemy(Enemy **tab_enemy)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        Enemy *enemy = malloc(sizeof(Enemy));
        Position *position = malloc(sizeof(Position));

        enemy->position = position;

        tab_enemy[i] = enemy;
    }
}
double normal_delay(double mean)
{
    return -mean * log(1 - ((double)rand() / RAND_MAX));
}

int is_inside_hitbox(Rocket *rocket, Enemy *enemy)
{
    if (rocket->hitbox->position->x + rocket->hitbox->size > enemy->hitbox->position->x && rocket->hitbox->position->x < enemy->hitbox->position->x + enemy->hitbox->size && rocket->hitbox->position->y + rocket->hitbox->size > enemy->hitbox->position->y && rocket->hitbox->position->y < enemy->hitbox->position->y + enemy->hitbox->size)
    {
        return 1;
    }
    return 0;
}

void enemy_shoot(Game *game)
{
    for (int i = 0; i < game->number_enemies_key; i++)
    {
        if (normal_delay(1) < 0.02 && game->tab_enemy[i]->is_alive == 1 && game->tab_enemy[i]->is_special == 0)
        {
            Rocket *rocket = malloc(sizeof(Rocket));
            Position *position = malloc(sizeof(Position));
            position->x = game->tab_enemy[i]->position->x - game->tab_enemy[i]->size;
            position->y = game->tab_enemy[i]->position->y - game->tab_enemy[i]->size / 2;
            rocket->position = position;
            rocket->size = ROCKET_ENNEMY_SIZE;
            rocket->speed = 15;
            rocket->damage = 1;
            rocket->is_alive = 1;
            rocket->is_player = 0;
            Hitbox *hitbox = malloc(sizeof(Hitbox));
            hitbox->position = rocket->position;
            hitbox->size = rocket->size;
            rocket->hitbox = hitbox;

            Position *position_shoot = malloc(sizeof(Position));

            rocket->position_shoot = position_shoot;
            game->tab_rocket[game->number_rocket_key] = rocket;

            game->number_rocket_key++;
        }
        else if (normal_delay(1) < 0.015 && game->tab_enemy[i]->is_alive == 1 && game->tab_enemy[i]->is_special == 1)
        {
            Rocket *rocket = malloc(sizeof(Rocket));
            Position *position = malloc(sizeof(Position));
            position->x = game->tab_enemy[i]->position->x;
            position->y = game->tab_enemy[i]->position->y + SIZE_ENEMY_TANK/2.2;
            rocket->position = position;
            rocket->size = ROCKET_ENNEMY_SIZE;
            rocket->speed = 5;
            rocket->damage = 1;
            rocket->is_alive = 1;
            rocket->is_player = 0;
            rocket->time = 200;
            Hitbox *hitbox = malloc(sizeof(Hitbox));
            hitbox->position = rocket->position;
            hitbox->size = rocket->size;
            rocket->hitbox = hitbox;

            rocket->is_special = 1;
            rocket->time_explosion = TIME_EXPLOSION_SPECIAL_ROCKET;

            // pour tete chercheuse
            Position *position_shoot = malloc(sizeof(Position));

            rocket->position_shoot = position_shoot;
            game->tab_rocket[game->number_rocket_key] = rocket;

            game->tab_rocket[game->number_rocket_key] = rocket;

            game->number_rocket_key++;
        }
    }
}

void touch_by_rocket(Game *game)
{

    rocket_available(game);
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        for (int j = 0; j < NUMBER_OF_ROCKET; j++)
        {

            if (game->tab_rocket[j]->is_alive == 1 && game->tab_enemy[i]->is_alive == 1 && is_inside_hitbox(game->tab_rocket[j], game->tab_enemy[i]) && game->tab_rocket[j]->is_player == 1)
            {
                game->tab_rocket[j]->is_alive = 0;

                game->tab_enemy[i]->health -= game->tab_rocket[j]->damage;
                game->player->score += 10;

                if (game->tab_enemy[i]->health <= 0)
                {
                    game->player->score += 100;
                    game->tab_enemy[i]->is_alive = 0;
                }
            }
        }
    }
}
void move(Game *game)
{
    for (int i = 0; i < game->number_enemies_key; i++)
    {
        game->tab_enemy[i]->position->x -= game->tab_enemy[i]->speed;
        Hitbox *hitbox = malloc(sizeof(Hitbox));
        hitbox->position = game->tab_enemy[i]->position;
        hitbox->size = game->tab_enemy[i]->size;
        game->tab_enemy[i]->hitbox = hitbox;
    }
}

void create_enemy(Game *game)
{
    Enemy *enemy = malloc(sizeof(Enemy));
    Position *position = malloc(sizeof(Position));
    position->x = WIDTH_FRAME + SIZE_ENEMY;
    position->y = rand() % (HEIGHT_FRAME - 50);
    enemy->position = position;

    enemy->size = SIZE_ENEMY;
    Hitbox *hitbox = malloc(sizeof(Hitbox));
    hitbox->position = enemy->position;
    hitbox->size = enemy->size;
    enemy->hitbox = hitbox;
    enemy->health = HEALTH_ENEMY;
    enemy->speed = 5;
    enemy->damage = 10;
    enemy->is_alive = 1;
    enemy->is_special = 0;

    game->tab_enemy[game->number_enemies_key] = enemy;
    game->number_enemies_key++;
}

void create_special_enemy(Game *game)
{
    for (int i = 0; i < game->number_enemies_key; i++)
    {
        if (game->tab_enemy[i]->is_special == 1 && game->tab_enemy[i]->hitbox->position->x < WIDTH_FRAME + SIZE_ENEMY && game->tab_enemy[i]->hitbox->position->x > WIDTH_FRAME - SIZE_ENEMY * 3)
        {
            return;
        }
    }
    Enemy *enemy = malloc(sizeof(Enemy));
    enemy->size = SIZE_ENEMY_TANK;
    Position *position = malloc(sizeof(Position));
    position->x = WIDTH_FRAME;
    position->y = HEIGHT_FRAME - enemy->size;
    enemy->position = position;

    Hitbox *hitbox = malloc(sizeof(Hitbox));
    hitbox->position = enemy->position;
    hitbox->size = enemy->size;
    enemy->hitbox = hitbox;
    enemy->health = HEALTH_SPECIAL_ENEMY;
    enemy->speed = 1;
    enemy->damage = 10;
    enemy->is_alive = 1;
    enemy->is_special = 1;

    game->tab_enemy[game->number_enemies_key] = enemy;
    game->number_enemies_key++;
}

void enemies_available(Game *game)
{
    for (int i = 0; i < game->number_enemies_key; i++)
    {

        if (game->tab_enemy[i]->position->x < 0 - game->tab_enemy[i]->size)
        {
            for (int j = i + 1; j < game->number_enemies_key; j++)
            {
                game->tab_enemy[j - 1] = game->tab_enemy[j];
            }
            game->number_enemies_key--;
        }
    }
}

void move_enemies(Game *game)
{
    if (normal_delay(15) < 0.0)
        create_enemy(game);

    if (normal_delay(15) < 0.7)
        create_special_enemy(game);

    enemies_available(game);
    touch_by_rocket(game);
    move(game);
    enemy_shoot(game);

    for (int i = 0; i < game->number_enemies_key; i++)
    {

        if (game->tab_enemy[i]->is_alive)
        {

            if (game->tab_enemy[i]->is_special)
            {
                draw_enemy_health(game->tab_enemy[i]);

                draw_enemy(game->tab_enemy[i], game->image->img_enemy_tank);
            }
            else
            {
                draw_enemy(game->tab_enemy[i], game->image->img_enemy);
            }
        }
    }
}
