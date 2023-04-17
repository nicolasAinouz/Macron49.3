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

Rocket *tab_rocket[NUMBER_OF_ROCKET];
int number_rocket = 0;

Enemy *tab_enemy_view[NUMBER_OF_ENEMY];
int number_enemies = 0;

MLV_Image *img_rocket;
MLV_Image *img_enemy;
MLV_Image *img;

int init_window()
{
    MLV_create_window(NAME_FRAME, NULL, WIDTH_FRAME, HEIGHT_FRAME);
    MLV_clear_window(MLV_COLOR_WHITE);
    img = MLV_load_image("src/data/vaisseau.png");
    img_rocket = MLV_load_image("src/data/rocket.png");
    img_enemy = MLV_load_image("src/data/rocket.png");
    for (int i = 0; i < NUMBER_OF_ROCKET; i++)
    {
        Rocket *rocket = malloc(sizeof(Rocket));
        rocket->position.x = 0;
        rocket->position.y = 0;
        rocket->size = 0;
        rocket->speed = 0;
        rocket->damage = 0;
        rocket->is_alive = 0;
        rocket->is_player = 0;

        tab_rocket[i] = rocket;
    }

    for (int i = 0; i < NUMBER_OF_ENEMY; i++)
    {
        Enemy *enemy = malloc(sizeof(Enemy));
        enemy->position.x = 0;
        enemy->position.y = 0;
        enemy->size = 0;
        enemy->speed = 0;
        enemy->damage = 0;
        tab_enemy_view[i] = enemy;
    }

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

    MLV_resize_image_with_proportions(img, get_player_size(), get_player_size());
    MLV_draw_image(img, get_player_position_x(), get_player_position_y());

    move_rocket();
    get_tab_rocket(tab_rocket, number_rocket);
    number_rocket = get_number_rocket();

    for (int i = 0; i < number_rocket; i++)
    {
        if (tab_rocket[i]->is_alive == 1)
        {
            MLV_resize_image_with_proportions(img_rocket, tab_rocket[i]->size, tab_rocket[i]->size);
            MLV_draw_image(img_rocket, tab_rocket[i]->position.x, tab_rocket[i]->position.y);
        }
    }

    get_tab_enemy(tab_enemy_view, number_enemies);
    number_enemies = get_number_enemies();

    for (int i = 0; i < number_enemies; i++)
    {
        if (tab_enemy_view[i]->is_alive == 1)
        {
            MLV_resize_image_with_proportions(img_enemy, tab_enemy_view[i]->size, tab_enemy_view[i]->size);
            MLV_draw_image(img_enemy, tab_enemy_view[i]->position.x, tab_enemy_view[i]->position.y);
        }
    }

   

    
    MLV_draw_text(10, 30, "Health : ", MLV_COLOR_RED);
    for(int i = 0; i < get_player_health(); i++)
    {
        MLV_draw_filled_rectangle(10 + (i * 20), 50, 10, 10, MLV_COLOR_RED);
    }

    MLV_draw_text(10, 70, "Score : ", MLV_COLOR_RED);

    int entier = get_player_score();

    char chaine[100];

    sprintf(chaine, "%d", entier);
    MLV_draw_text(10, 90,chaine, MLV_COLOR_RED);


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
   
   

    free(img);
    free(img_rocket);
    free(img_enemy);

    return EXIT_SUCCESS;
}
