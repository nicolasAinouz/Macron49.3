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

void set_image(Game *game)
{
    game->image->img_player = MLV_load_image("src/assets/img/player.png");
    game->image->img_rocket = MLV_load_image("src/assets/img/rocket.png");
    game->image->img_enemy_tank = MLV_load_image("src/assets/img/tank.png");
    game->image->img_enemy = MLV_load_image("src/assets/img/air_soldat.png");
    game->image->img_bullet_tank = MLV_load_image("src/assets/img/ammo_tank.png");
    game->image->img_background = MLV_load_image("src/assets/img/background.jpg");
    game->image->img_explosion = MLV_load_image("src/assets/img/explosion.png");
    game->image->img_bullet_player = MLV_load_image("src/assets/img/bullet_player.png");

    game->image->img_powerup_dbz = MLV_load_image("src/assets/img/powerup_dbz_logo.png");
    MLV_resize_image_with_proportions(game->image->img_powerup_dbz, 90, 90);

    game->image->img_player_dbz = MLV_load_image("src/assets/img/player_power_up_dbz.png");
    game->image->img_explosion_dbz = MLV_load_image("src/assets/img/kamehameha.png");
    game->image->img_powerup_health = MLV_load_image("src/assets/img/coeur.png");

    game->image->img_powerup_speed = MLV_load_image("src/assets/img/speed.png");
}
void set_sound(Game *game)
{
    game->sounddbz = MLV_load_sound("src/assets/sound/Kamehameha_Goku_SOUND_EFFECT.ogg");
    game->music = MLV_load_music("src/assets/sound/background_music.mp3");
}
void set_font(Game *game)
{
    game->font = MLV_load_font("src/assets/font/fontScore.ttf", 30);
}
void init_window(Game *game)
{
    MLV_change_window_size(WIDTH_FRAME, HEIGHT_FRAME);

    MLV_clear_window(MLV_COLOR_WHITE);
    if (MLV_init_audio())
    {
        fprintf(stderr, "L'infrasctructure audio de la librairie MLV ne s'est pas correctement initialisé.");
        exit(1);
    }
    set_image(game);
    set_sound(game);
    set_font(game);
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

void draw_powerup_in_game(Game *game)
{
    if (game->powerup->in_the_game)
    {
        switch (game->powerup->type)
        {
        case 0:
            break;
        case 1:
            MLV_resize_image_with_proportions(game->image->img_powerup_dbz, SIZE_POWER_UP, SIZE_POWER_UP);
            MLV_draw_image(game->image->img_powerup_dbz, game->powerup->position->x, game->powerup->position->y);

            break;
        case 2:
            MLV_resize_image_with_proportions(game->image->img_powerup_health, SIZE_POWER_UP, SIZE_POWER_UP);
            MLV_draw_image(game->image->img_powerup_health, game->powerup->position->x, game->powerup->position->y);

            break;
        case 3:
            MLV_resize_image_with_proportions(game->image->img_powerup_speed, SIZE_POWER_UP, SIZE_POWER_UP);
            MLV_draw_image(game->image->img_powerup_speed, game->powerup->position->x, game->powerup->position->y);

            break;
        default:
            break;
        }
    }
}

void draw_powerup_square(Game *game)
{
    MLV_draw_filled_rectangle(WIDTH_FRAME - PADDING_TOP * 1.1, 10, PADDING_TOP - 10, PADDING_TOP - 10, MLV_rgba(0, 0, 0, 120));

    switch (game->player->powerup->type)
    {
    case 0:
        break;
    case 1:
        MLV_resize_image_with_proportions(game->image->img_powerup_dbz, PADDING_TOP - 10, PADDING_TOP - 10);
        MLV_draw_image(game->image->img_powerup_dbz, WIDTH_FRAME - PADDING_TOP * 1.1, 10);
        break;
    case 2:
        MLV_resize_image_with_proportions(game->image->img_powerup_health, PADDING_TOP - 10, PADDING_TOP - 10);
        MLV_draw_image(game->image->img_powerup_health, WIDTH_FRAME - PADDING_TOP * 1.1, 10);
        break;
    default:
    case 3:
        MLV_resize_image_with_proportions(game->image->img_powerup_speed, PADDING_TOP - 10, PADDING_TOP - 10);
        MLV_draw_image(game->image->img_powerup_speed, WIDTH_FRAME - PADDING_TOP * 1.1, 10);
        break;
    }
}

void draw_powerup(Game *game)
{
    draw_powerup_square(game);
    draw_powerup_in_game(game);
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
    if (rocket->is_alive)
    {
        MLV_resize_image_with_proportions(img_rocket, rocket->size, rocket->size);
        MLV_draw_image(img_rocket, rocket->position->x, rocket->position->y);
    }
}

void draw_player(Game *game)
{
    if (game->player->powerup->is_actif && game->player->powerup->type == 1)
    {

        MLV_resize_image_with_proportions(game->image->img_player_dbz, game->player->size * 2, game->player->size * 2);
        MLV_draw_image(game->image->img_player_dbz, game->player->position->x, game->player->position->y);
        if (game->player->powerup->animation < 70)
        {
            MLV_draw_image(game->image->img_explosion_dbz, game->player->position->x - 150, game->player->position->y - 300);
        }
    }
    else
    {
        MLV_resize_image_with_proportions(game->image->img_player, game->player->size, game->player->size);
        MLV_draw_image(game->image->img_player, game->player->position->x, game->player->position->y);
    }
}

void draw_health(Game *game)
{
    MLV_draw_rectangle(9, 9, (HEALTH_PLAYER * SIZE_PLAYER / 2) + 2, 12, MLV_COLOR_BLANCHED_ALMOND);
    if (game->player->health > HEALTH_PLAYER / 3)
        MLV_draw_filled_rectangle(10, 10, game->player->health * SIZE_PLAYER / 2, 10, MLV_COLOR_GREEN);
    else
        MLV_draw_filled_rectangle(10, 10, game->player->health * SIZE_PLAYER / 2, 10, MLV_COLOR_RED);
}

void draw_score(Game *game)
{
    int value = game->player->score;

    char chaine[100];

    sprintf(chaine, "%d", value);
    MLV_draw_text_with_font(10, 30, chaine, game->font, MLV_COLOR_BLACK);
}

/**
 *
 * @brief redessine la window
 *
 * @param player
 * @return int
 */
void draw_window(Game *game)
{
    MLV_draw_image(game->image->img_background, game->scale + WIDTH_FRAME, 0);
    MLV_draw_image(game->image->img_background, game->scale, 0);
}

void draw_explosion(int x, int y, MLV_Image *img_explosion)
{

    MLV_draw_image(img_explosion, x, y);
}

void draw_power_up_dbz(Game *game)
{
    if (game->player->powerup->animation == 180)
    {
        MLV_play_sound(game->sounddbz, 1.0);
    }
}

int draw_input_name(Game *game)
{
    // char *player_name;

    MLV_draw_adapted_text_box_with_font(400, 150, "GAME OVER", game->font, 30, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_rgba(0, 0, 0, 100), MLV_TEXT_CENTER);
    // party->player->name = player_name;

    return EXIT_SUCCESS;
}
void print_game_over(Game *game)
{
    MLV_draw_adapted_text_box_with_font(400, 150, "GAME OVER", game->font, 30, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_rgba(0, 0, 0, 100), MLV_TEXT_CENTER);
    char chaine[100];
    sprintf(chaine, "Score : %d", game->player->score);
    MLV_draw_adapted_text_box_with_font(400, 250, chaine, game->font, 30, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_rgba(0, 0, 0, 100), MLV_TEXT_CENTER);
    MLV_draw_text_with_font(200, 360, "Pseudo :", game->font, MLV_COLOR_WHITE);
    MLV_wait_input_box_with_font(400, 350, 300, 50, MLV_COLOR_INDIAN_RED, MLV_COLOR_INDIAN_RED, MLV_rgba(0, 0, 0, 10), "", &game->pseudo, game->font);
}

void draw_shoot_bar(Game *game)
{
    MLV_draw_rectangle(WIDTH_FRAME - PADDING_TOP * 2.5, PADDING_TOP / 3, 100, 10, MLV_COLOR_BLACK);
    if (game->player->shoot > 0)
    {
        if (game->player->is_shooting_too_much)
        {
            MLV_draw_filled_rectangle(WIDTH_FRAME - PADDING_TOP * 2.5, PADDING_TOP / 3, game->player->shoot, 10, MLV_COLOR_INDIANRED);
        }
        else
        {
            MLV_draw_filled_rectangle(WIDTH_FRAME - PADDING_TOP * 2.5, PADDING_TOP / 3, game->player->shoot, 10, MLV_COLOR_ORANGE_RED);
        }
    }
}
