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

void init_window()
{
    MLV_create_window(NAME_FRAME, NULL, WIDTH_FRAME, HEIGHT_FRAME);
    MLV_clear_window(MLV_COLOR_WHITE);

    img = MLV_load_image("src/data/vaisseau.png");
    img_rocket = MLV_load_image("src/data/rocket.png");
    img_enemy = MLV_load_image("src/data/rocket.png");

    

    

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
int draw_window()
{

    MLV_resize_image_with_proportions(img, get_player_size(), get_player_size());
    MLV_draw_image(img, get_player_position_x(), get_player_position_y());

    MLV_draw_text(10, 30, "Health : ", MLV_COLOR_RED);
    for (int i = 0; i < get_player_health(); i++)
    {
        MLV_draw_filled_rectangle(10 + (i * 20), 50, 10, 10, MLV_COLOR_RED);
    }

    MLV_draw_text(10, 70, "Score : ", MLV_COLOR_RED);

    int entier = get_player_score();

    char chaine[100];

    sprintf(chaine, "%d", entier);
    MLV_draw_text(10, 90, chaine, MLV_COLOR_RED);

    return 0;
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
