#include <MLV/MLV_all.h>
#include "../include/const.h"

void launch_home()
{
    MLV_create_window(NAME_FRAME, NULL, 600, 700);
    MLV_Image *img_background = MLV_load_image("src/assets/img/home_bg.png");
    MLV_Font *font = MLV_load_font("src/assets/font/fontScore.ttf", 30);
    MLV_resize_image(img_background, 600, 700);
    MLV_draw_image(img_background, 0, 0);

    MLV_draw_adapted_text_box_with_font(120, 450, "Macron 49.3", font, 30, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_rgba(0, 0, 0, 100), MLV_TEXT_CENTER);
    MLV_draw_adapted_text_box_with_font(220, 550, "PLAY", font, 10, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_rgba(0, 0, 0, 100), MLV_TEXT_CENTER);
    MLV_actualise_window();
    MLV_free_image(img_background);
    MLV_free_font(font);
}

int click_on_play(int x, int y)
{
    if (x >= 220 && x <= 355 && y >= 550 && y <= 605)
        return 1;
    return 0;
}