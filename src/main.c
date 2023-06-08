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
 * @brief Function that free the image structure
 * 
 * @return Image_Game* The image structure
 */
void free_image(Image_Game *imgs)
{
    MLV_free_image(imgs->img_background);
    MLV_free_image(imgs->img_bullet_player);
    MLV_free_image(imgs->img_bullet_tank);
    MLV_free_image(imgs->img_enemy);
    MLV_free_image(imgs->img_enemy_tank);
    MLV_free_image(imgs->img_explosion);
    MLV_free_image(imgs->img_explosion_dbz);
    MLV_free_image(imgs->img_player);
    MLV_free_image(imgs->img_player_dbz);
    MLV_free_image(imgs->img_powerup_dbz);
    MLV_free_image(imgs->img_powerup_health);
    MLV_free_image(imgs->img_powerup_speed);
    MLV_free_image(imgs->img_rocket);

    free(imgs);
}

/**
 * @brief Function that free the player structure
 * 
 * @param player player structure
 */
void free_player(Player *player)
{
    if (player->powerup != NULL)
    {
        free(player->powerup->position);
        free(player->powerup);
    }
    free(player->position);
    free(player);
}

/**
 * @brief Function that free the rockets structure
 * 
 * @param tab_rocket tab of rockets
 */
void free_rockets(Rocket **tab_rocket)
{
    for (int i = 0; i < NUMBER_OF_ROCKET; i++)
    {
        if (tab_rocket[i] != NULL)
        {
            if (tab_rocket[i]->position != NULL)
                free(tab_rocket[i]->position);
            if (tab_rocket[i]->hitbox != NULL)
                free(tab_rocket[i]->hitbox);
        }
    }
    if (*tab_rocket != NULL)
        free(*tab_rocket);
}

/**
 * @brief Function that free the ennemies structure
 * 
 * @param tab_enemy tab of ennemies
 */
void free_ennemies(Enemy **tab_enemy)
{
    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        if (tab_enemy[i] != NULL)
        {
            if (tab_enemy[i]->position != NULL)
                free(tab_enemy[i]->position);
            if (tab_enemy[i]->hitbox != NULL)
                free(tab_enemy[i]->hitbox);
        }
    }

    free(*tab_enemy);
}

/**
 * @brief Function that coordinate the free of all the structure
 * 
 * @param game the game structure
 */
void free_all(Game *game)
{
    free_image(game->image);

    if (game->powerup != NULL)
    {
        if (game->powerup->position != NULL)
            free(game->powerup->position);

        free(game->powerup);
    }

    MLV_free_font(game->font);

    free_player(game->player);

    // free_rockets(game->tab_rocket);

    // free_ennemies(game->tab_enemy);

    // MLV_stop_music();

    // MLV_free_sound(game->sounddbz);

    // MLV_free_music(game->music);

    // MLV_free_audio();

    MLV_free_window();
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
