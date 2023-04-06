#include <MLV/MLV_all.h>
#include <MLV/MLV_time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/const.h"
#include "include/window.h"
#include "include/key_listener.h"
#include "include/player_controller.h"

int main(int argc, char const *argv[])
{
    int end_game = 0;
    int time_frame;

    

    /* permet de récupérer les temps de début et de fin (pour vérifier si la frame est pas trop rapide)*/
    struct timespec start_time, end_time;

    /* création de la frame */
    init_window();
    init_player();

    while (end_game == 0)
    {
        /* Récupération de l'heure au début */
        clock_gettime(CLOCK_REALTIME, &start_time);

        /* Ici le code */

        /* refresh de la window*/
        clear_window();
        draw_window();
        
        //On récupère les évènements clavier
        key_listener();

        /* Récupération de l'heure en fin */
        clock_gettime(CLOCK_REALTIME, &end_time);
        time_frame = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_nsec - start_time.tv_nsec) / BILLION);

        /* Si la frame a été trop vite, on attend un peu */
        if (time_frame < (1.0 / 30.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 30.0) - time_frame) * 1000));
        }
    }

    /* libération mémoire window */
    free_window();
    return EXIT_SUCCESS;
}
