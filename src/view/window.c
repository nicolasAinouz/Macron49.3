#include <MLV/MLV_all.h>
#include <math.h>

#include "../include/const.h"
#include "../include/key_listener.h"
#include "../include/player_controller.h"
#include "../include/struct_entity.h"
#include "../include/enemies_controller.h"

/**
 * @brief initialisation de la window
 *
 * @return int
 */

// MLV_Sound *sound;

void init_window(Game *game)
{
    MLV_create_window(NAME_FRAME, NULL, WIDTH_FRAME, HEIGHT_FRAME);
    MLV_clear_window(MLV_COLOR_WHITE);
    if (MLV_init_audio())
    {
        fprintf(stderr, "L'infrasctructure audio de la librairie MLV ne s'est pas correctement initialisé.");
        exit(1);
    }

    

    game->image->img_player = MLV_load_image("src/assets/player.png");
    game->image->img_rocket = MLV_load_image("src/assets/rocket.png");
    game->image->img_enemy_tank = MLV_load_image("src/assets/tank.png");
    game->image->img_enemy = MLV_load_image("src/assets/rocket.png");
    game->image->img_bullet_tank = MLV_load_image("src/assets/ammo_tank.png");
    game->image->img_background = MLV_load_image("src/assets/background.jpg");
    game->image->img_explosion = MLV_load_image("src/assets/explosion.png");
    game->image->img_bullet_player = MLV_load_image("src/assets/bullet_player.png");

    // temporaire
    game->image->img_powerup_dbz = MLV_load_image("src/assets/powerup_dbz_logo.png");
    MLV_resize_image_with_proportions(game->image->img_powerup_dbz, 90, 90);

    game->image->img_player_dbz = MLV_load_image("src/assets/player_power_up_dbz.png");
    game->sounddbz = MLV_load_sound("src/assets/sound/Kamehameha_Goku_SOUND_EFFECT.ogg");
}

/**
 * @brief efface le contenu de la window
 *
 * @return int
 */
int clear_window()
{
    MLV_clear_window(MLV_COLOR_WHITE);
    return EXIT_SUCCESS;
}

/**
 * @brief
 *
 * @param enemy
 */
void draw_enemy(Enemy *enemy, MLV_Image *img_enemy)
{
    MLV_resize_image_with_proportions(img_enemy, enemy->size, enemy->size);
    MLV_draw_image(img_enemy, enemy->position->x, enemy->position->y);
}

void draw_enemy_health(Enemy *enemy)
{

    if (enemy->health > HEALTH_SPECIAL_ENEMY / 3)
        MLV_draw_filled_rectangle(enemy->position->x, enemy->position->y - 10, enemy->health * 3, 5, MLV_COLOR_GREEN);
    else
        MLV_draw_filled_rectangle(enemy->position->x, enemy->position->y - 10, enemy->health * 3, 5, MLV_COLOR_RED);
}

void draw_rocket(Rocket *rocket, MLV_Image *img_rocket)

{
    MLV_resize_image_with_proportions(img_rocket, rocket->size, rocket->size);
    MLV_draw_image(img_rocket, rocket->position->x, rocket->position->y);
}

/**
 *
 * @brief redessine la window
 *
 * @param player
 * @return int
 */
int draw_window(Game* game, Player *player, int scale, MLV_Image *img_background, MLV_Image *img_player)
{
    // MLV_play_sound(sound, 1.0);

    MLV_draw_image(img_background, scale + WIDTH_FRAME, 0);
    MLV_draw_image(img_background, scale, 0);

    if (!player->powerup->is_actif)
    {
        MLV_resize_image_with_proportions(img_player, player->size, player->size);
        MLV_draw_image(img_player, player->position->x, player->position->y);
    }else{
        MLV_resize_image_with_proportions(game->image->img_player_dbz, game->player->size + 100, game->player->size + 100);
    MLV_draw_image(game->image->img_player_dbz, game->player->position->x, game->player->position->y);
    }

    MLV_draw_rectangle(9, 9, (HEALTH_PLAYER * SIZE_PLAYER / 2) + 2, 12, MLV_COLOR_BLANCHED_ALMOND);
    if (player->health > HEALTH_PLAYER / 3)
        MLV_draw_filled_rectangle(10, 10, player->health * SIZE_PLAYER / 2, 10, MLV_COLOR_GREEN);
    else
        MLV_draw_filled_rectangle(10, 10, player->health * SIZE_PLAYER / 2, 10, MLV_COLOR_RED);

    MLV_draw_text(10, 30, "Score : ", MLV_COLOR_RED);

    int entier = player->score;

    char chaine[100];

    sprintf(chaine, "%d", entier);
    MLV_draw_text(10, 40, chaine, MLV_COLOR_RED);

    return 0;
}

void draw_explosion(int x, int y, MLV_Image *img_explosion)
{

    MLV_draw_image(img_explosion, x, y);
}

void draw_powerup(Game *game)
{
    MLV_draw_rectangle(WIDTH_FRAME - PADDING_TOP * 1.1, 10, PADDING_TOP - 10, PADDING_TOP - 10, MLV_COLOR_BLACK);
    MLV_draw_image(game->image->img_powerup_dbz, WIDTH_FRAME - PADDING_TOP * 1.1, 10);
}

void draw_power_up_dbz(Game *game)
{
    if (game->player->powerup->animation == 10000)
    {
        MLV_play_sound(game->sounddbz, 1.0);
    }
    
    game->player->powerup->animation--;
    if (game->player->powerup->animation == 0)
    {
        game->player->powerup->type = 0;
        game->player->powerup->is_actif = 0;
    }
}

/**
 * @brief libère en mémoire la window
 *
 * @return int
 */
int free_window()
{
    MLV_free_window();

    // free(img);
    // free(img_rocket);
    // free(img_enemy);

    return EXIT_SUCCESS;
}
