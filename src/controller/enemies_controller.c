#include <MLV/MLV_all.h>
#include <math.h>
#include <stdlib.h>

#include "../include/const.h"
#include "../include/struct_entity.h"

Enemy *tab_enemy[NUMBER_OF_ENEMY];
int number_enemies_key = 0;

void printvalue(int value)
{
    printf("%d ", value);
}
double normal_delay(double mean)
{
    return -mean * log(1 - ((double)rand() / RAND_MAX));
}

void move_enemies()
{
    for (int i = 0; i < number_enemies_key; i++)
    {
        tab_enemy[i]->position.y += tab_enemy[i]->speed;
    }
}

void create_enemy()
{
    Enemy *enemy = malloc(sizeof(Enemy));

    enemy->position.x = rand() % (WIDTH_FRAME - 50);
    enemy->position.y = -50;
    enemy->size = 50;
    enemy->health = 100;
    enemy->speed = 10;
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
    move_enemies();
    fflush(stdout);
    printf("number_enemies \n");
    printvalue(number_enemies_key);
    printf("size \n");
    printvalue(size);
    
    for (int i = 0; i < number_enemies_key; i++)
    {
        tab_enemy_old[i]->position = tab_enemy[i]->position;
        tab_enemy_old[i]->size = tab_enemy[i]->size;
        tab_enemy_old[i]->health = tab_enemy[i]->health;
        tab_enemy_old[i]->speed = tab_enemy[i]->speed;
        tab_enemy_old[i]->damage = tab_enemy[i]->damage;
        tab_enemy_old[i]->is_alive = tab_enemy[i]->is_alive;
    }
    // if (number_enemies_key < size - 1)
    // {
    //     for (int i = number_enemies_key; i < size; i++)
    //     {
            
    //         tab_enemy_old[i]->position.x = 0;
    //         tab_enemy_old[i]->position.y = 0;
    //         tab_enemy_old[i]->size = 0;
    //         tab_enemy_old[i]->health = 0;
    //         tab_enemy_old[i]->speed = 0;
    //         tab_enemy_old[i]->damage = 0;
    //         tab_enemy_old[i]->is_alive = 0;
    //     }
    // }
}
