#include <MLV/MLV_all.h>
#include <math.h>
#include <stdlib.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/key_listener.h"

Enemy *tab_enemy[NUMBER_OF_ENEMY];
Rocket *tab_rocket[NUMBER_OF_ROCKET];
int number_enemies_key = 0;

void printvalue(int value)
{
    printf("%d ", value);
}
double normal_delay(double mean)
{
    return -mean * log(1 - ((double)rand() / RAND_MAX));
}

int is_inside_hitbox(Rocket *rocket, Enemy *enemy)
{
    if (rocket->hitbox.position.x + rocket->hitbox.size > enemy->hitbox.position.x && rocket->hitbox.position.x < enemy->hitbox.position.x + enemy->hitbox.size && rocket->hitbox.position.y + rocket->hitbox.size > enemy->hitbox.position.y && rocket->hitbox.position.y < enemy->hitbox.position.y + enemy->hitbox.size)
    {
        return 1;
    }
    return 0;
}

void enemy_shoot()
{
    for (int i = 0; i < number_enemies_key; i++)
    {
        if (normal_delay(1) < 0.05 && tab_enemy[i]->is_alive == 1)
        {
            Rocket *rocket = malloc(sizeof(Rocket));
            rocket->position.x = tab_enemy[i]->position.x + tab_enemy[i]->size / 2;
            rocket->position.y = tab_enemy[i]->position.y + tab_enemy[i]->size;
            rocket->size = 10;
            rocket->speed = 15;
            rocket->damage = 1;
            rocket->is_alive = 1;
            Hitbox hitbox;
            hitbox.position = rocket->position;
            hitbox.size = rocket->size;
            rocket->hitbox = hitbox;
            rocket->is_player = 0;
            tab_rocket[get_number_rocket()] = rocket;

            set_number_rocket(get_number_rocket() + 1);
        }
    }
}

void touch_by_rocket()
{
    get_tab_rocket(tab_rocket, get_number_rocket());
    for (int i = 0; i < number_enemies_key; i++)
    {
        for (int j = 0; j < get_number_rocket(); j++)
        {
            if (is_inside_hitbox(tab_rocket[j], tab_enemy[i]))
            {
                tab_enemy[i]->health -= tab_rocket[j]->damage;
                if (tab_enemy[i]->health <= 0)
                    tab_enemy[i]->is_alive = 0;
            }
        }
    }
}
void move_enemies()
{
    for (int i = 0; i < number_enemies_key; i++)
    {
        tab_enemy[i]->position.y += tab_enemy[i]->speed;
        Hitbox hitbox;
        hitbox.position = tab_enemy[i]->position;
        hitbox.size = tab_enemy[i]->size;
        tab_enemy[i]->hitbox = hitbox;
    }
}

void create_enemy()
{
    Enemy *enemy = malloc(sizeof(Enemy));

    enemy->position.x = rand() % (WIDTH_FRAME - 50);
    enemy->position.y = -50;
    enemy->size = 50;
    Hitbox hitbox;
    hitbox.position = enemy->position;
    hitbox.size = enemy->size;
    enemy->hitbox = hitbox;
    enemy->health = 100;
    enemy->speed = 5;
    enemy->damage = 10;
    enemy->is_alive = 1;

    tab_enemy[number_enemies_key] = enemy;
    number_enemies_key++;
}

void enemies_available()
{
    for (int i = 0; i < number_enemies_key; i++)
    {
        if (tab_enemy[i]->position.y > HEIGHT_FRAME + tab_enemy[i]->size)
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

void get_tab_enemy(Enemy **tab_enemy_old, int size)
{
    if (normal_delay(15) < 1)
        create_enemy();

    // printf("number_enemies : %d \n", number_enemies_key);

    enemies_available();
    touch_by_rocket();
    move_enemies();
    enemy_shoot();

    for (int i = 0; i < number_enemies_key; i++)
    {
        tab_enemy_old[i]->position = tab_enemy[i]->position;
        tab_enemy_old[i]->size = tab_enemy[i]->size;
        tab_enemy_old[i]->health = tab_enemy[i]->health;
        tab_enemy_old[i]->speed = tab_enemy[i]->speed;
        tab_enemy_old[i]->damage = tab_enemy[i]->damage;
        tab_enemy_old[i]->is_alive = tab_enemy[i]->is_alive;
        tab_enemy_old[i]->hitbox = tab_enemy[i]->hitbox;
    }
}
