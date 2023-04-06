#include <MLV/MLV_all.h>

#include "../include/const.h"
#include "../include/key_listener.h"
#include "../include/player_controller.h"
#include "../include/struct_entity.h"

/**
 * @brief initialisation de la window
 *
 * @return int
 */

Rocket *tab_rocket[NUMBER_OF_ROCKET];
int number_rocket = 0;

Enemy *tab_enemy[NUMBER_OF_ENEMY];

int init_window()
{
    MLV_create_window(NAME_FRAME, NULL, WIDTH_FRAME, HEIGHT_FRAME);
    MLV_clear_window(MLV_COLOR_WHITE);
    return EXIT_SUCCESS;
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
 * @brief redessine la window
 *
 * @param player
 * @return int
 */
int draw_window()
{

    MLV_Image *img = MLV_load_image("src/data/vaisseau.png");
    MLV_resize_image_with_proportions(img, get_player_size(), get_player_size());
    MLV_draw_image(img, get_player_position_x(), get_player_position_y());
    MLV_Image *img_rocket = MLV_load_image("src/data/rocket.png");

    get_tab_rocket(tab_rocket, number_rocket);
    number_rocket = get_number_rocket();

    for (int i = 0; i < number_rocket; i++)
    {
        MLV_resize_image_with_proportions(img_rocket, tab_rocket[i]->size, tab_rocket[i]->size);
        MLV_draw_image(img_rocket, tab_rocket[i]->position.x, tab_rocket[i]->position.y);
        tab_rocket[i]->position.y -= tab_rocket[i]->speed;
    }

    
    free(img);
    free(img_rocket);

    MLV_actualise_window();

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

    return EXIT_SUCCESS;
}
