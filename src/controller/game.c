/**
 * @file game.c
 * @brief It's the controller of the structure game and the utils functions
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
#include <math.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/enemies_controller.h"
#include "../include/player_controller.h"
#include "../include/key_listener.h"
#include "../include/rocket_controller.h"

/**
 * @brief Function that generate random (Function from the Algorithmic course (Thanks Mr Thapper))
 *
 * @param mean the mean of the random
 * @return double the random
 */
double normal_delay(double mean)
{
    return -mean * log(1 - ((double)rand() / RAND_MAX));
}

/**
 * @brief Initialise the structure of the game who contains all the structure of the game
 *
 * @return Game* the game structure
 */
Game *create_game()
{

    Game *game = malloc(sizeof(Game));
    assert(game != NULL);

    game->player = malloc(sizeof(Player));
    assert(game->player != NULL);

    Player *player = init_player();

    init_tab_enemy(game->tab_enemy);
    
    init_tab_rocket(game->tab_rocket);

    Image_Game *image_game = malloc(sizeof(Image_Game));
    assert(image_game != NULL);

    Powerup *powerup = malloc(sizeof(Powerup));
    assert(powerup != NULL);
    game->powerup = powerup;

    game->image = image_game;
    game->player = player;

    game->difficulty = 1;

    return game;
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

    free_rockets(game->tab_rocket);

    free_ennemies(game->tab_enemy);

    MLV_stop_music();

    MLV_free_sound(game->sounddbz);

    MLV_free_music(game->music);

    MLV_free_audio();

    MLV_free_window();
}
