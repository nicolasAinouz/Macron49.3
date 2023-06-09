/**
 * @file main.c
 * @brief Main file of the project
 * @details This file contains the game loop and the main function
 * @author Nicolas Ainouz
 * @version 1.0
 * @date 08/06/2022
 */

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

/**
 * @brief Function that launch the home screen
 *
 */
void home()
{
    launch_home();

    int exit = 0;
    int mouse_x, mouse_y;
    while (!exit)
    {
        MLV_wait_mouse(&mouse_x, &mouse_y);
        exit = click_on_play(mouse_x, mouse_y);
    }
}

/**
 * @brief Function that move the background
 * @param game The game structure
 *
 */
void move_scale(Game *game)
{
    game->scale -= 1;
    if (game->scale <= -WIDTH_FRAME)
    {
        game->scale = 0;
    }
}

/**
 * @brief Function that do the actions on the powerup like move it, draw it
 *
 * @param game The game structure
 */
void update_powerup(Game *game)
{
    if (game->powerup->in_the_game == 0 && normal_delay(30) < 0.1 && game->player->powerup->type == 0 && !game->player->powerup->is_actif)
        create_powerup(game);

    if (game->powerup->in_the_game)
    {
        move_powerup(game);
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
    draw_powerup(game);
}
/**
 * @brief Function that add difficulty to the game
 *
 * @param game The game structure
 */
void add_difficulty(Game *game)
{
    if (game->player->score % 1000 == 0)
    {
        game->difficulty += 0.1;
    }
}

/**
 * @brief Function that write the score of the player in a file
 *
 * @param game the game structure
 */
void write_score(Game *game)
{
    FILE *file = fopen("src/assets/score.txt", "a");
    assert(file != NULL);

    fprintf(file, "Player : %s -> Score : %d -> on : %s at : %s \n", game->pseudo, game->player->score, __DATE__, __TIME__);
    fclose(file);
}

/**
 * @brief Main function of the project contain the game loop
 *
 * @param argc number of arguments
 * @param argv arguments
 * @return int
 */
int main(int argc, char const *argv[])
{
    int time_frame;
    Game *game = create_game();
    assert(game != NULL);

    home();

    init_window(game);

    struct timespec start_time, end_time;
    MLV_play_music(game->music, 0.2, -1);

    while (game->end_game == 0 && !player_is_dead(game))
    {

        game->player->score += 1;

        add_difficulty(game);
        move_scale(game);

        clock_gettime(CLOCK_REALTIME, &start_time);

        MLV_clear_window(MLV_COLOR_BLACK);
        draw_window(game);

        move_enemies(game);
        move_rocket(game);

        key_listener(game);
        update_powerup(game);
        player_update(game);

        MLV_actualise_window();

        clock_gettime(CLOCK_REALTIME, &end_time);
        time_frame = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_nsec - start_time.tv_nsec) / BILLION);

        if (time_frame < (1.0 / 30.0))
        {
            MLV_wait_milliseconds((int)(((1.0 / 30.0) - time_frame) * 1000));
        }
    }
    if (player_is_dead(game))
    {
        print_game_over(game);
        write_score(game);
    }

    free_all(game);
    return EXIT_SUCCESS;
}
