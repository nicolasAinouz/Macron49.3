#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/const.h"
#include "../include/window.h"
#include "../include/struct_entity.h"
#include "../include/player_controller.h"

/**
 * @brief Récupère les évènements clavier
 *
 * @param key
 */
Rocket *tab_rocket[NUMBER_OF_ROCKET];
int number_rocket_key = 0;

void rocket_available()
{
    for (int i = 0; i < number_rocket_key; i++)
    {
        if (tab_rocket[i]->position.y < 0)
        {
            for (int j = i; j < number_rocket_key; j++)
            {
                tab_rocket[j] = tab_rocket[j + 1];
            }
            number_rocket_key--;
        }
    }
}

int get_number_rocket()
{
    return number_rocket_key;
}

void get_tab_rocket(Rocket **tab_rocket_old, int size)
{
    rocket_available();
    for (int i = 0; i < number_rocket_key; i++)
    {
        tab_rocket_old[i]->position = tab_rocket[i]->position;
        tab_rocket_old[i]->size = tab_rocket[i]->size;
        tab_rocket_old[i]->speed = tab_rocket[i]->speed;
        tab_rocket_old[i]->damage = tab_rocket[i]->damage;
    }
    if (number_rocket_key < size)
    {
        for (int i = number_rocket_key; i < size; i++)
        {

            free(tab_rocket[i]);
        }
    }
}

void shoot()
{

    Rocket *rocket = malloc(sizeof(Rocket));

    rocket->position.x = get_player_position_x() + get_player_size() / 2;
    rocket->position.y = get_player_position_y();
    rocket->size = 20;
    rocket->speed = 30;
    rocket->damage = 50;

    tab_rocket[number_rocket_key] = rocket;
    number_rocket_key++;
}

void key_listener()

{
    MLV_Keyboard_button key;
    MLV_Button_state state;
    MLV_get_event(&key, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
    if (state == MLV_PRESSED)
    {
        if (key == MLV_KEYBOARD_LEFT)
        {
            move_player_left();
        }
        else if (key == MLV_KEYBOARD_RIGHT)
        {
            move_player_right();
        }
        else if (key == MLV_KEYBOARD_UP)
        {
            move_player_up();
        }
        else if (key == MLV_KEYBOARD_DOWN)
        {
            move_player_down();
        }
        else if (key == MLV_KEYBOARD_SPACE)
        {
            shoot();
        }
    }
}
