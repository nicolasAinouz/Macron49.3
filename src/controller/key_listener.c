#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/main.h"
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

void move_rocket()
{
    for (int i = 0; i < number_rocket_key; i++)
    {
        if (tab_rocket[i]->is_player == 0)
        {
            tab_rocket[i]->position.y += tab_rocket[i]->speed;
        }
        else
        {
            tab_rocket[i]->position.y -= tab_rocket[i]->speed;
        }
        Hitbox hitbox;
        hitbox.position = tab_rocket[i]->position;
        hitbox.size = tab_rocket[i]->size;
        tab_rocket[i]->hitbox = hitbox;
    }
}

int rocket_touch_player(Rocket *rocket)
{
    if (rocket->is_player == 0)
    {
        if (rocket->hitbox.position.x + rocket->hitbox.size > get_player_position().x && rocket->hitbox.position.x < get_player_position().x + get_player_size() && rocket->hitbox.position.y + rocket->hitbox.size > get_player_position().y && rocket->hitbox.position.y < get_player_position().y + get_player_size())
        {
            return 1;
        }
    }
    return 0;
}

void rocket_available()
{
    for (int i = 0; i < number_rocket_key; i++)
    {
        if (tab_rocket[i]->position.y + tab_rocket[i]->size < 0 || tab_rocket[i]->position.y > WIDTH_FRAME + 100)
        {
            for (int j = i + 1; j < number_rocket_key; j++)
            {
                tab_rocket[j - 1] = tab_rocket[j];
            }
            number_rocket_key--;
        }
        if(rocket_touch_player(tab_rocket[i]))
        {
            set_player_health(get_player_health() - tab_rocket[i]->damage);
            for (int j = i + 1; j < number_rocket_key; j++)
            {
                tab_rocket[j - 1] = tab_rocket[j];
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
        tab_rocket_old[i] = tab_rocket[i];
    }
}

void set_number_rocket(int number)
{
    number_rocket_key = number;
}

void shoot()
{

    Rocket *rocket = malloc(sizeof(Rocket));

    rocket->position.x = get_player_position_x() + get_player_size() / 2 - ROCKET_SIZE / 3;
    rocket->position.y = get_player_position_y() - ROCKET_SIZE / 3;
    rocket->size = ROCKET_SIZE;
    Hitbox hitbox;
    hitbox.position = rocket->position;
    hitbox.size = rocket->size;
    rocket->hitbox = hitbox;
    rocket->speed = 30;
    rocket->damage = 100;
    rocket->is_alive = 1;
    rocket->is_player = 1;

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
        else if (key == MLV_KEYBOARD_ESCAPE)
        {
            end_game_signal();
        }
    }
}
