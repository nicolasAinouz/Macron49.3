#include <MLV/MLV_all.h>

#include "../include/const.h"


/**
 * @brief initialisation de la window
 * 
 * @return int 
 */
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
    printf("chn\n");
    MLV_Image *img;
    img = MLV_load_image("../data/ship.png");
    MLV_resize_image_with_proportions(img, 10, 10);
    MLV_draw_image(img, 10, 10);
    MLV_actualise_window();
    return EXIT_SUCCESS;
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