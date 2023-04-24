#include <MLV/MLV_all.h>

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

MLV_Image *img_rocket;
MLV_Image *img_enemy;
MLV_Image *img;
MLV_Image *img_background;
MLV_Image *img_explosion;
// MLV_Sound *sound;

void init_window()
{
    MLV_create_window(NAME_FRAME, NULL, WIDTH_FRAME, HEIGHT_FRAME);
    MLV_clear_window(MLV_COLOR_WHITE);
    // if (MLV_init_audio())
    // {
    //     fprintf(stderr, "L'infrasctructure audio de la librairie MLV ne s'est pas correctement initialisé.");
    //     exit(1);
    // }

    // sound = MLV_load_sound("src/assets/sound/explosion.ogg");

    img = MLV_load_image("src/assets/vaisseau.png");
    img_rocket = MLV_load_image("src/assets/rocket.png");
    img_enemy = MLV_load_image("src/assets/rocket.png");
    img_background = MLV_load_image("src/assets/background.jpg");
    img_explosion = MLV_load_image("src/assets/boom_4.png");
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
void draw_enemy(Enemy *enemy)
{

    MLV_resize_image_with_proportions(img_enemy, enemy->size, enemy->size);
    MLV_draw_image(img_enemy, enemy->position->x, enemy->position->y);
}

void draw_rocket(Rocket *rocket)
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
int draw_window(Player *player, int scale)
{
    // MLV_play_sound(sound, 1.0);
    
    MLV_draw_image(img_background, scale + WIDTH_FRAME, 0);
    MLV_draw_image(img_background, scale, 0);

    MLV_resize_image_with_proportions(img, player->size, player->size);
    MLV_draw_image(img, player->position->x, player->position->y);

    MLV_draw_text(10, 30, "Health : ", MLV_COLOR_RED);
    for (int i = 0; i < player->health; i++)
    {
        MLV_draw_filled_rectangle(10 + (i * 20), 50, 10, 10, MLV_COLOR_RED);
    }

    MLV_draw_text(10, 70, "Score : ", MLV_COLOR_RED);

    int entier = player->score;

    char chaine[100];

    sprintf(chaine, "%d", entier);
    MLV_draw_text(10, 90, chaine, MLV_COLOR_RED);

    return 0;
}

void draw_explosion(int x, int y){

}

/**
 * @brief libère en mémoire la window
 *
 * @return int
 */
int free_window()
{
    MLV_free_window();

    free(img);
    free(img_rocket);
    free(img_enemy);

    return EXIT_SUCCESS;
}
