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
        Position *position = malloc(sizeof(Position));
        position->x = 0;
        position->y = 0;
        rocket->position = position;
        rocket->size = 0;
        rocket->speed = 0;
        rocket->damage = 0;
        rocket->is_alive = 0;
        rocket->is_player = 0;

        tab_rocket[i] = rocket;
    }
}
/**
 * @brief Récupère les évènements clavier
 *
 * @param key
 */

int number_rocket_key = 0;
int last;

void move_rocket(Rocket **tab_rocket)
{
    for (int i = 0; i < number_rocket_key; i++)
    {

        if (tab_rocket[i]->is_player == 1)
        {
            tab_rocket[i]->position->y -= tab_rocket[i]->speed;
        }

        else if (tab_rocket[i]->is_special == 1 && tab_rocket[i]->position->y < get_player_position_y() +10)
        {

            float dx = (float)(get_player_position_x() - tab_rocket[i]->position->x);
            float dy = (float)(get_player_position_y() - tab_rocket[i]->position->y);
            float length = sqrt(dx * dx + dy * dy);
            float dirx = dx / length;
            float diry = dy / length;

            float move_x = dirx * tab_rocket[i]->speed;
            float move_y = diry * tab_rocket[i]->speed;

            tab_rocket[i]->position->x += move_x;
            tab_rocket[i]->position->y += move_y;
        }
        else
        {
            tab_rocket[i]->position->y += tab_rocket[i]->speed;
        }
        Hitbox *hitbox = malloc(sizeof(Hitbox));
        hitbox->position = tab_rocket[i]->position;
        hitbox->size = tab_rocket[i]->size;
        tab_rocket[i]->hitbox = hitbox;
        if (tab_rocket[i]->is_alive == 1)
            draw_rocket(tab_rocket[i]);
    }
}

int rocket_touch_player(Rocket *rocket)
{
    if (rocket->is_player == 0)
    {
        if (rocket->hitbox->position->x + rocket->hitbox->size > get_player_position()->x && rocket->hitbox->position->x < get_player_position()->x + get_player_size() && rocket->hitbox->position->y + rocket->hitbox->size > get_player_position()->y && rocket->hitbox->position->y < get_player_position()->y + get_player_size())
        {
            return 1;
        }
    }
    return 0;
}

void rocket_available(Rocket **tab_rocket)
{
    for (int i = 0; i < number_rocket_key; i++)
    {
        if (tab_rocket[i]->position->y + tab_rocket[i]->size < 0 || tab_rocket[i]->position->y > WIDTH_FRAME + 100)
        {
            for (int j = i + 1; j < number_rocket_key; j++)
            {
                tab_rocket[j - 1] = tab_rocket[j];
            }
            number_rocket_key--;
        }
        if (rocket_touch_player(tab_rocket[i]))
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

void set_number_rocket(int number)
{
    number_rocket_key = number;
}

void shoot(Rocket **tab_rocket)
{

    Rocket *rocket = malloc(sizeof(Rocket));

    Position *position = malloc(sizeof(Position));
    position->x = get_player_position()->x + get_player_size() / 2 - ROCKET_SIZE / 3;
    position->y = get_player_position()->y - ROCKET_SIZE / 3;
    rocket->position = position;

    rocket->size = ROCKET_SIZE;

    Hitbox *hitbox = malloc(sizeof(Hitbox));
    hitbox->position = rocket->position;
    hitbox->size = rocket->size;
    rocket->hitbox = hitbox;

    rocket->speed = 30;
    rocket->damage = 100;

    rocket->is_alive = 1;
    rocket->is_player = 1;
    rocket->is_special = 0;

    tab_rocket[number_rocket_key] = rocket;
    number_rocket_key++;
}

void key_listener(Rocket **tab_rocket)
{

    int bool = 0;
    move_rocket(tab_rocket);

    if (get_player_speed() > 2)
    {

        set_player_speed(get_player_speed() - 2);
    }
    else
    {
        last = 0;
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED)
    {
        set_player_speed(20);
        move_player_left();
        last = 1;
        bool = 1;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED)
    {
        set_player_speed(20);
        move_player_up();
        last = 2;
        bool = 1;
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED)
    {
        set_player_speed(20);
        move_player_right();
        last = 3;
        bool = 1;
    }

    if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED)
    {
        set_player_speed(20);
        move_player_down();
        last = 4;
        bool = 1;
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED)
    {
        shoot(tab_rocket);
    }
    if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED)
    {
        end_game_signal();
    }
    if (bool == 0)
    {
        if (last == 1)
        {

            move_player_left();
        }
        if (last == 2)
        {
            move_player_up();
        }
        if (last == 3)
        {
            move_player_right();
        }
        if (last == 4)
        {
            move_player_down();
        }
    }

    bool = 1;
}
