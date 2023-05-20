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

void print_tab_rockey_key(Game *game)
{
    for (int i = 0; i < game->number_rocket_key; i++)
    {
        printf("rocket %d : %d\n", i, game->tab_rocket[i]->is_alive);
        printf("rocket specifities : %d %d %d %d %d %d %d\n", game->tab_rocket[i]->position->x, game->tab_rocket[i]->position->y, game->tab_rocket[i]->size, game->tab_rocket[i]->speed, game->tab_rocket[i]->damage, game->tab_rocket[i]->is_player, game->tab_rocket[i]->is_special);
    }
}

void init_tab_enemy(Enemy **tab_enemy)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        Enemy *enemy = malloc(sizeof(Enemy));
        assert(enemy != NULL);
        Position *position = malloc(sizeof(Position));
        assert(position != NULL);

        enemy->position = position;

        tab_enemy[i] = enemy;
    }
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
        if (normal_delay(1) < 0.010 && game->tab_enemy[i]->is_alive == 1 && game->tab_enemy[i]->is_special == 0)
        {
            shoot(game, game->tab_enemy[i], 0, 0);
        }
        else if (normal_delay(1) < 0.01 && game->tab_enemy[i]->is_alive == 1 && game->tab_enemy[i]->is_special == 1)
        {
            shoot(game, game->tab_enemy[i], 1, 0);
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

                if (game->tab_enemy[i]->health <= 0)
                {

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
int check_distance_enemy(Game *game)
{
    for (int i = 0; i < game->number_enemies_key; i++)
    {
        if (game->tab_enemy[i]->is_special == 1 && game->tab_enemy[i]->hitbox->position->x < WIDTH_FRAME + SIZE_ENEMY && game->tab_enemy[i]->hitbox->position->x > WIDTH_FRAME - SIZE_ENEMY * 3)
        {
            return 0;
        }
    }
    return 1;
}

void create_enemy(Game *game, int is_special)
{
    if (is_special && !check_distance_enemy(game))
    {
        return;
    }
    Enemy *enemy = malloc(sizeof(Enemy));
    assert(enemy != NULL);
    Position *position = malloc(sizeof(Position));
    assert(position != NULL);
    Hitbox *hitbox = malloc(sizeof(Hitbox));
    assert(hitbox != NULL);
    switch (is_special)
    {
    case 0:
        enemy->size = SIZE_ENEMY;
        position->x = WIDTH_FRAME + SIZE_ENEMY;
        position->y = rand() % (HEIGHT_FRAME - (SIZE_ENEMY * 2));
        if (position->y < PADDING_TOP)
        {
            int x = PADDING_TOP - position->y;
            position->y += x;
        }
        enemy->health = HEALTH_ENEMY;
        enemy->speed = SPEED_ENEMY;
        enemy->is_special = 0;
        break;
    case 1:
        enemy->size = SIZE_ENEMY_TANK;
        position->x = WIDTH_FRAME;
        position->y = HEIGHT_FRAME - enemy->size;
        enemy->health = HEALTH_SPECIAL_ENEMY;
        enemy->speed = SPEED_SPECIAL_ENEMY;
        enemy->is_special = 1;

        break;
    default:
        break;
    }
    enemy->position = position;
    hitbox->position = enemy->position;
    hitbox->size = enemy->size;
    enemy->hitbox = hitbox;
    enemy->is_alive = 1;
    game->tab_enemy[game->number_enemies_key] = enemy;
    game->number_enemies_key++;
}

void enemies_available(Game *game)
{
    for (int i = 0; i < game->number_enemies_key; i++)
    {

        if (game->tab_enemy[i]->position->x < 0 - game->tab_enemy[i]->size)
        {
            if (game->tab_enemy[i]->is_alive == 1)
            {
                game->player->health -= 1;
            }
            for (int j = i + 1; j < game->number_enemies_key; j++)
            {
                game->tab_enemy[j - 1] = game->tab_enemy[j];
            }

            game->number_enemies_key--;
        }
    }
}
int is_inside_player_hitbox(Enemy *enemy, Player *player)
{
    if (enemy->hitbox->position->x < player->hitbox->position->x + player->hitbox->size && enemy->hitbox->position->x + enemy->hitbox->size > player->hitbox->position->x && enemy->hitbox->position->y < player->hitbox->position->y + player->hitbox->size && enemy->hitbox->position->y + enemy->hitbox->size > player->hitbox->position->y)
    {
        return 1;
    }
    return 0;
}
int is_inside_ulti_hitbox(Enemy *enemy, Player *player)
{
    if (enemy->hitbox->position->x < player->hitbox->position->x + player->hitbox->size + 900 && enemy->hitbox->position->x + enemy->hitbox->size > player->hitbox->position->x + 90 && enemy->hitbox->position->y < player->hitbox->position->y + player->hitbox->size + 100 && enemy->hitbox->position->y + enemy->hitbox->size > player->hitbox->position->y - 100)
    {

        return 1;
    }
    return 0;
}

void enemy_touch_player(Game *game)
{
    for (int i = 0; i < game->number_enemies_key; i++)
    {
        if (game->tab_enemy[i]->is_alive == 1 && is_inside_player_hitbox(game->tab_enemy[i], game->player))
        {
            if (!(game->player->powerup->is_actif == 1 && game->player->powerup->type == 1))
            {
                game->tab_enemy[i]->is_alive = 0;
                game->player->health -= 1;
            }
        }
    }
}

void touch_by_ultime(Game *game)
{
    for (int i = 0; i < game->number_enemies_key; i++)
    {
        if (game->tab_enemy[i]->is_alive == 1 && is_inside_ulti_hitbox(game->tab_enemy[i], game->player) && game->player->powerup->is_actif && game->player->powerup->type == 1 && game->player->powerup->animation < 70)
        {
            game->tab_enemy[i]->is_alive = 0;
        }
    }
}

void call_view(Game *game)
{
    for (int i = 0; i < game->number_enemies_key; i++)
    {

        if (game->tab_enemy[i]->is_alive)
        {
            game->tab_enemy[i]->is_special ? draw_enemy(game->tab_enemy[i], game->image->img_enemy_tank), draw_enemy_health(game->tab_enemy[i]) : draw_enemy(game->tab_enemy[i], game->image->img_enemy);
        }
    }
}

void move_enemies(Game *game)
{
    if (normal_delay(30) < 0.3)
        create_enemy(game, 0);

    if (normal_delay(30) < 0.1)
        create_enemy(game, 1);

    enemies_available(game);
    touch_by_rocket(game);
    touch_by_ultime(game);
    move(game);
    enemy_shoot(game);
    enemy_touch_player(game);

    call_view(game);
}
