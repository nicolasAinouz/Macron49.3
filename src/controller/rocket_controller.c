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

        Position *position_shoot = malloc(sizeof(Position));
        assert(position != NULL);
        rocket->position_shoot = position_shoot;

        tab_rocket[i] = rocket;
    }
}
/**
 * @brief Récupère les évènements clavier
 *
 * @param key
 */

void move_rocket(Game *game)
{
    for (int i = 0; i < game->number_rocket_key; i++)
    {
        if (game->tab_rocket[i]->is_alive == 1)
        {

            if (game->tab_rocket[i]->is_player == 1)
            {
                game->tab_rocket[i]->position->x += game->tab_rocket[i]->speed;
            }
            // tete chercheuse
            else if (game->tab_rocket[i]->is_special == 1)
            {
                game->tab_rocket[i]->time -= 1;
                if (game->tab_rocket[i]->time < 0 && game->tab_rocket[i]->time_explosion > 0)
                {
                    game->tab_rocket[i]->damage = 0;
                    
                    draw_explosion(game->tab_rocket[i]->position->x, game->tab_rocket[i]->position->y, game->image->img_explosion);
                    game->tab_rocket[i]->time_explosion--;
                }else if (game->tab_rocket[i]->time_explosion == 0)
                {
                    game->tab_rocket[i]->is_alive = 0;
                }
                else
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

            }

            else
            {
                game->tab_rocket[i]->position->x -= game->tab_rocket[i]->speed;
            }

            if (game->tab_rocket[i]->is_player)
                draw_rocket(game->tab_rocket[i], game->image->img_bullet_player);
            else
            {
                if (game->tab_rocket[i]->is_special == 1 && game->tab_rocket[i]->time > 0)
                {
                    draw_rocket(game->tab_rocket[i], game->image->img_bullet_tank);
                }
                else if (game->tab_rocket[i]->is_special == 0)
                {
                    draw_rocket(game->tab_rocket[i], game->image->img_bullet_tank);
                }
               
            }

        }
    }

}

int rocket_touch_player(Rocket *rocket, Player *player)
{

    if (!rocket->is_player)
    {

        if (rocket->hitbox->position->x + rocket->hitbox->size > player->position->x && rocket->hitbox->position->x < player->position->x + player->size && rocket->hitbox->position->y + rocket->hitbox->size > player->position->y && rocket->hitbox->position->y < player->position->y + player->size)
        {
            printf("rocket touch player\n");

            return 1;
        }
    }
    return 0;
}

void rocket_available(Game *game)
{
    for (int i = 0; i < game->number_rocket_key; i++)
    {
        if (game->tab_rocket[i]->position->x < 0 + game->tab_rocket[i]->size || game->tab_rocket[i]->position->x > WIDTH_FRAME)
        {
            for (int j = i + 1; j < game->number_rocket_key; j++)
            {
                game->tab_rocket[i]->damage = 0;

                game->tab_rocket[j - 1] = game->tab_rocket[j];
            }
            game->number_rocket_key--;
        }
        if (rocket_touch_player(game->tab_rocket[i], game->player))
        {
            game->player->health -= game->tab_rocket[i]->damage;
            game->tab_rocket[i]->damage = 0;
            game->tab_rocket[i]->is_alive = 0;

            for (int j = i + 1; j < game->number_rocket_key; j++)
            {
                game->tab_rocket[j - 1] = game->tab_rocket[j];
            }
            game->number_rocket_key--;
        }
    }
}

void shoot(Game *game)
{

    Rocket *rocket = malloc(sizeof(Rocket));
    assert(rocket != NULL);

    Position *position = malloc(sizeof(Position));
    assert(position != NULL);
    position->x = game->player->position->x + game->player->size;
    position->y = game->player->position->y;
    rocket->position = position;
    rocket->is_player = 1;

    rocket->size = ROCKET_SIZE;

    Hitbox *hitbox = malloc(sizeof(Hitbox));
    assert(hitbox != NULL);
    hitbox->position = rocket->position;
    hitbox->size = rocket->size;
    rocket->hitbox = hitbox;

    rocket->speed = 30;
    rocket->damage = 5;

    rocket->is_alive = 1;
    rocket->is_player = 1;
    rocket->is_special = 0;

    Position *position_shoot = malloc(sizeof(Position));
    assert(position_shoot != NULL);
    position_shoot->x = 0;
    position_shoot->y = 0;
    rocket->position_shoot = position_shoot;

    game->tab_rocket[game->number_rocket_key] = rocket;
    game->number_rocket_key++;
}