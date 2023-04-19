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

int number_rocket_key = 0;

void move_rocket(Rocket *tab_rocket)
{
    for (int i = 0; i < number_rocket_key; i++)
    {
        if (tab_rocket[i].is_player == 0)
        {
            tab_rocket[i].position.y += tab_rocket[i].speed;
        }
        else
        {
            tab_rocket[i].position.y -= tab_rocket[i].speed;
        }
        Hitbox hitbox;
        hitbox.position = tab_rocket[i].position;
        hitbox.size = tab_rocket[i].size;
        tab_rocket[i].hitbox = hitbox;
        if (tab_rocket[i].is_alive == 1)
            draw_rocket(tab_rocket[i]);
    }
}

int rocket_touch_player(Rocket rocket)
{
    if (rocket.is_player == 0)
    {
        if (rocket.hitbox.position.x + rocket.hitbox.size > get_player_position().x && rocket.hitbox.position.x < get_player_position().x + get_player_size() && rocket.hitbox.position.y + rocket.hitbox.size > get_player_position().y && rocket.hitbox.position.y < get_player_position().y + get_player_size())
        {
            return 1;
        }
    }
    return 0;
}

void rocket_available(Rocket * tab_rocket)
{
    for (int i = 0; i < number_rocket_key; i++)
    {
        if (tab_rocket[i].position.y + tab_rocket[i].size < 0 || tab_rocket[i].position.y > WIDTH_FRAME + 100)
        {
            for (int j = i + 1; j < number_rocket_key; j++)
            {
                tab_rocket[j - 1] = tab_rocket[j];
            }
            number_rocket_key--;
        }
        if (rocket_touch_player(tab_rocket[i]))
        {
            set_player_health(get_player_health() - tab_rocket[i].damage);
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


void set_number_rocket(int number)
{
    number_rocket_key = number;
}

void shoot(Rocket *tab_rocket)
{

    Rocket rocket;

    rocket.position.x = get_player_position_x() + get_player_size() / 2 - ROCKET_SIZE / 3;
    rocket.position.y = get_player_position_y() - ROCKET_SIZE / 3;
    rocket.size = ROCKET_SIZE;
    Hitbox hitbox;
    hitbox.position = rocket.position;
    hitbox.size = rocket.size;
    rocket.hitbox = hitbox;
    rocket.speed = 30;
    rocket.damage = 100;
    rocket.is_alive = 1;
    rocket.is_player = 1;

    tab_rocket[number_rocket_key] = rocket;
    number_rocket_key++;
}

void key_listener(Rocket *tab_rocket)
{
    move_rocket(tab_rocket);

    if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)
    {
        move_player_left();
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED)
    {
        move_player_up();
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)
    {
        move_player_right();
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED)
    {
        move_player_down();
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED)
    {
        shoot(tab_rocket);
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED)
    {
        end_game_signal();
    }
}
