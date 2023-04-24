#include <MLV/MLV_all.h>
#include <MLV/MLV_time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
    // Game *game = malloc(sizeof(Game));
    // assert(game != NULL);
    // game->tab_enemy = malloc(sizeof(Enemy *) * NUMBER_OF_ENEMY);
    // assert(game->tab_enemy != NULL);
    // game->tab_rocket = malloc(sizeof(Rocket *) * NUMBER_OF_ROCKET);

    // game->player = malloc(sizeof(Player));
    // assert(game->player != NULL);

    // game->player = init_player();


    Enemy *tab_enemy[100];
    Rocket *tab_rocket[100];
    // game->tab_enemy = tab_enemy;
    // game->tab_rocket = tab_rocket;
    Player *player = init_player();

    

    init_tab_enemy(tab_enemy);
    
    init_tab_rocket(tab_rocket);

    init_window();
    
    

    struct timespec start_time, end_time;
int scale = 0;
    while (end_game == 0)
    {
        scale -= 1;
        if(scale <= -WIDTH_FRAME )
        {
            scale = 0;
        }
        fflush(stdout);
       
        clock_gettime(CLOCK_REALTIME, &start_time);

        clear_window();
        draw_window(player, scale);

        move_enemies(tab_enemy, tab_rocket, player);
        
        

        key_listener(tab_rocket, player);
        MLV_actualise_window();

        clock_gettime(CLOCK_REALTIME, &end_time);
        time_frame = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_nsec - start_time.tv_nsec) / BILLION);

        if (time_frame < (1.0 / 30.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 30.0) - time_frame) * 1000));
        }
    }

    free_window();
    MLV_free_audio();
    return EXIT_SUCCESS;
}
