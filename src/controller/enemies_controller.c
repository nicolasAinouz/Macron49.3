#include <MLV/MLV_all.h>
#include <math.h>
#include <stdlib.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/key_listener.h"
#include "../include/player_controller.h"
#include "../include/window.h"

int number_enemies_key = 0;

void init_tab_enemy(Enemy **tab_enemy)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        Enemy *enemy = malloc(sizeof(Enemy));
        Position *position = malloc(sizeof(Position));
        position->x = 0;
        position->y = 0;
        enemy->position = position;

        enemy->size = 0;
        enemy->speed = 0;
        enemy->damage = 0;
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

void enemy_shoot(Enemy **tab_enemy, Rocket **tab_rocket)
{
    for (int i = 0; i < number_enemies_key; i++)
    {
        if (normal_delay(1) < 0.02 && tab_enemy[i]->is_alive == 1 && tab_enemy[i]->is_special == 0)
        {
            Rocket *rocket = malloc(sizeof(Rocket));
            Position *position = malloc(sizeof(Position));
            position->x = tab_enemy[i]->position->x + tab_enemy[i]->size / 2;
            position->y = tab_enemy[i]->position->y + tab_enemy[i]->size;
            rocket->position = position;
            rocket->size = ROCKET_ENNEMY_SIZE;
            rocket->speed = 15;
            rocket->damage = 1;
            rocket->is_alive = 1;
            Hitbox *hitbox = malloc(sizeof(Hitbox));
            hitbox->position = rocket->position;
            hitbox->size = rocket->size;
            rocket->hitbox = hitbox;
            rocket->is_player = 0;
            rocket->is_special = 0;
            tab_rocket[get_number_rocket()] = rocket;

            set_number_rocket(get_number_rocket() + 1);
        }
        else if (normal_delay(1) < 0.005 && tab_enemy[i]->is_alive == 1 && tab_enemy[i]->is_special == 1)
        {
           Rocket *rocket = malloc(sizeof(Rocket));
            Position *position = malloc(sizeof(Position));
            position->x = tab_enemy[i]->position->x + tab_enemy[i]->size / 2;
            position->y = tab_enemy[i]->position->y + tab_enemy[i]->size;
            rocket->position = position;
            rocket->size = ROCKET_ENNEMY_SIZE;
            rocket->speed = 5;
            rocket->damage = 1;
            rocket->is_alive = 1;
            Hitbox *hitbox = malloc(sizeof(Hitbox));
            hitbox->position = rocket->position;
            hitbox->size = rocket->size;
            rocket->hitbox = hitbox;
            rocket->is_player = 0;
            rocket->is_special = 1;
            tab_rocket[get_number_rocket()] = rocket;

            set_number_rocket(get_number_rocket() + 1);
        }
    }
}

void touch_by_rocket(Enemy **tab_enemy, Rocket **tab_rocket)
{

    rocket_available(tab_rocket);
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        for (int j = 0; j < NUMBER_OF_ROCKET; j++)
        {

            if (tab_rocket[j]->is_alive == 1 && tab_enemy[i]->is_alive == 1 && is_inside_hitbox(tab_rocket[j], tab_enemy[i]))
            {

                tab_enemy[i]->health -= tab_rocket[j]->damage;
                set_player_score(get_player_score() + 20);

                if (tab_enemy[i]->health <= 0)
                {
                    set_player_score(get_player_score() + 100);
                    tab_enemy[i]->is_alive = 0;
                }
            }
        }
    }
}
void move(Enemy **tab_enemy)
{
    for (int i = 0; i < number_enemies_key; i++)
    {
        tab_enemy[i]->position->y += tab_enemy[i]->speed;
        Hitbox *hitbox = malloc(sizeof(Hitbox));
        hitbox->position = tab_enemy[i]->position;
        hitbox->size = tab_enemy[i]->size;
        tab_enemy[i]->hitbox = hitbox;
    }
}

void create_enemy(Enemy **tab_enemy)
{
    Enemy *enemy = malloc(sizeof(Enemy));
    Position *position = malloc(sizeof(Position));
    position->x = rand() % (WIDTH_FRAME - 50);
    position->y = -30;
    enemy->position = position;

    enemy->size = SIZE_ENEMY;
    Hitbox *hitbox = malloc(sizeof(Hitbox));
    hitbox->position = enemy->position;
    hitbox->size = enemy->size;
    enemy->hitbox = hitbox;
    enemy->health = 100;
    enemy->speed = 5;
    enemy->damage = 10;
    enemy->is_alive = 1;
    enemy->is_special = 0;

    tab_enemy[number_enemies_key] = enemy;
    number_enemies_key++;
}

void create_special_enemy(Enemy **tab_enemy)
{
    Enemy *enemy = malloc(sizeof(Enemy));
    Position *position = malloc(sizeof(Position));
    position->x = rand() % (WIDTH_FRAME - 50);
    position->y = -30;
    enemy->position = position;

    enemy->size = SIZE_ENEMY + 50;
    Hitbox *hitbox = malloc(sizeof(Hitbox));
    hitbox->position = enemy->position;
    hitbox->size = enemy->size;
    enemy->hitbox = hitbox;
    enemy->health = 500;
    enemy->speed = 1;
    enemy->damage = 10;
    enemy->is_alive = 1;
    enemy->is_special = 1;

    tab_enemy[number_enemies_key] = enemy;
    number_enemies_key++;
}

void enemies_available(Enemy **tab_enemy)
{
    for (int i = 0; i < number_enemies_key; i++)
    {
        if (tab_enemy[i]->position->y > HEIGHT_FRAME + tab_enemy[i]->size)
        {
            for (int j = i + 1; j < number_enemies_key; j++)
            {
                tab_enemy[j - 1] = tab_enemy[j];
            }
            number_enemies_key--;
        }
    }
}

int get_number_enemies()
{
    return number_enemies_key;
}

void move_enemies(Enemy **tab_enemy, Rocket **tab_rocket)
{
    if (normal_delay(15) < 0.3)
        create_enemy(tab_enemy);

    if (normal_delay(15) < 0.1)
        create_special_enemy(tab_enemy);

    enemies_available(tab_enemy);
    touch_by_rocket(tab_enemy, tab_rocket);
    move(tab_enemy);
    enemy_shoot(tab_enemy, tab_rocket);

    for (int i = 0; i < number_enemies_key; i++)
    {
        if (tab_enemy[i]->is_alive == 1)
            draw_enemy(tab_enemy[i]);
    }
}
