#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/const.h"
#include "include/window.h"

int main(int argc, char const *argv[])
{
    int end_game = 0;
    int time_frame;

    

    MLV_Event event;
    MLV_Keyboard_button key;
    MLV_Button_state state;

    /* permet de récupérer les temps de début et de fin (pour vérifier si la frame est pas trop rapide)*/
    struct timespec start_time, end_time;

    /* création de la frame */
    init_window();
    printf("chan");

    /* Initialisation de la game (création du player plus peut etre d'autres choses)*/
  
    /*
    Faire un draw_menu() ou on peut quitter le jeu ou jouer (peut etre choisir un niveau ??)
    Pour faire ca, on écrit du texte à x et y pixel, et quand on clique sur le texte avec la souris, soit on quitte, soit on lance le jeu
    (améliorations : au survole de la souris sur le texte, mettre un encadré ou qqch du genre)
    */
    while (end_game == 0)
    {
        /* Récupération de l'heure au début */
        clock_gettime(CLOCK_REALTIME, &start_time);

        /* Ici le code */

        /* refresh de la window*/
        clear_window();
        draw_window();
        

        /* je ne sais pas comment on récupère les différentes touches du clavier */
        /* Proposition : on se déplace avec les flèches clavier + on tire avec la touche espace */
        event = MLV_get_event(&key, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);

        if(state == MLV_PRESSED) {
            printf("touche\n");
           
        }

        /* refresh de la window */

        /* En fonction de l'event il faut faire des choses... */
        /*  vérification que le joueur ne sort pas de l'écran. S'il est encore sur l'écran :
            if flèche de gauche => déplacement à gauche (player.position.x-5)
            if flèche de droite => déplacement à droite (player.position.x+5)
            if flèche du haut => déplacement vers le haut (player.position.y-5)
            if flèche du bas => déplacement vers le bas (player.position.y+5)
        */

        /* Récupération de l'heure en fin */
        clock_gettime(CLOCK_REALTIME, &end_time);
        time_frame = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_nsec - start_time.tv_nsec) / BILLION);

        /* Si la frame a été trop vite, on attend un peu */
        if (time_frame < (1.0 / 48.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 48.0) - time_frame) * 1000));
        }
    }

    /* libération mémoire window */
    free_window();
    return EXIT_SUCCESS;
}
