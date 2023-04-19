#include <MLV/MLV_all.h>
#include <MLV/MLV_time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/const.h"
#include "include/window.h"
#include "include/key_listener.h"
#include "include/player_controller.h"
#include "include/enemies_controller.h"

int end_game = 0;

void end_game_signal()
{
    end_game = 1;
}

int main(int argc, char const *argv[])
{

    int time_frame;

    Enemy tab_enemy[100];
    Rocket tab_rocket[100];

    struct timespec start_time, end_time;

    init_window(tab_enemy, tab_rocket);

    init_player();

    while (end_game == 0)
    {
        clock_gettime(CLOCK_REALTIME, &start_time);

        clear_window();
        
        move_enemies(tab_enemy, tab_rocket);
        draw_window();

        key_listener(tab_rocket);
        MLV_actualise_window();

        clock_gettime(CLOCK_REALTIME, &end_time);
        time_frame = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_nsec - start_time.tv_nsec) / BILLION);

        if (time_frame < (1.0 / 30.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 30.0) - time_frame) * 1000));
        }
    }

    free_window();
    return EXIT_SUCCESS;
}
