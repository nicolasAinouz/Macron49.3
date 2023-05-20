#include <MLV/MLV_all.h>
#include <MLV/MLV_time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "include/const.h"
#include "include/struct_entity.h"
#include "include/window.h"
#include "include/key_listener.h"
#include "include/player_controller.h"
#include "include/enemies_controller.h"
#include "include/game.h"
#include "include/powerup.h"
#include "include/rocket_controller.h"
#include "include/home.h"

int main(int argc, char const *argv[])
{
    int time_frame;
    Game *game = create_game();
    assert(game != NULL);

    launch_home();

    int exit = 0;
    int mouse_x, mouse_y;
    while (!exit)
    {
        MLV_wait_mouse(&mouse_x, &mouse_y);
        exit = click_on_play(mouse_x, mouse_y);
    }

    init_window(game);

    struct timespec start_time, end_time;

    while (game->end_game == 0)
    {
        printf("index tab %d\n", game->number_enemies_key);
        printf("index tab rocket %d\n", game->number_rocket_key);
        game->player->score += 1;
        if (player_is_dead(game))
        {
            game->end_game = 1;
        }
        game->scale -= 1;
        if (game->scale <= -WIDTH_FRAME)
        {
            game->scale = 0;
        }

        clock_gettime(CLOCK_REALTIME, &start_time);

        MLV_clear_window(MLV_COLOR_BLACK);
        draw_window(game, game->player, game->scale, game->image->img_background, game->image->img_player);

        move_enemies(game);
        move_rocket(game);

        key_listener(game);
        if (game->powerup->in_the_game == 0 && normal_delay(15) < 5 && game->player->powerup->type == 0 && !game->player->powerup->is_actif)
            create_powerup(game);

        if (game->powerup->in_the_game)
        {
            move_powerup(game);
        }
        MLV_actualise_window();

        clock_gettime(CLOCK_REALTIME, &end_time);
        time_frame = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_nsec - start_time.tv_nsec) / BILLION);

        if (time_frame < (1.0 / 30.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 30.0) - time_frame) * 1000));
        }

        if (game->player->powerup->is_actif)
        {
            if (game->player->powerup->animation != 0)
            {
                game->player->powerup->animation -= 1;
            }
            else
            {
                game->player->powerup->type = 0;
                game->player->powerup->is_actif = 0;
                game->player->powerup->animation = 0;
            }
        }
      
    }
    if (player_is_dead(game))
    {
        print_game_over(game);
    }

    free_window();
    MLV_free_audio();
    return EXIT_SUCCESS;
}
