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

int end_game_signal()
{
    return 1;
}

int main(int argc, char const *argv[])
{
    int time_frame;
    Game *game = create_game();
    assert(game != NULL);

    init_window(game);

    struct timespec start_time, end_time;
    while (game->end_game == 0)
    {
        game->scale -= 1;
        if (game->scale <= -WIDTH_FRAME)
        {
            game->scale = 0;
        }

        clock_gettime(CLOCK_REALTIME, &start_time);

        clear_window();
        draw_window(game->player, game->scale, game->image->img_background, game->image->img_player);

        move_enemies(game);

        key_listener(game);
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
