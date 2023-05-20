#include <MLV/MLV_all.h>
#include <math.h>
#include <assert.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/window.h"

void create_powerup(Game *game)
{
    int x = rand() % NB_POWER_UP + 1;

    game->powerup->in_the_game = 1;
    game->powerup->type = x;
    game->powerup->speed = 5;
    Position *position = malloc(sizeof(Position));
    assert(position != NULL);
    position->x = WIDTH_FRAME;
    position->y = rand() % (HEIGHT_FRAME - SIZE_POWER_UP);
    if (position->y < PADDING_TOP)
    {
        int x = PADDING_TOP - position->y;
        position->y += x;
    }
    game->powerup->position = position;
    // game->powerup->position->x = WIDTH_FRAME;
    // game->powerup->position->y = rand() % (HEIGHT_FRAME - SIZE_POWER_UP);
}
int touch_powerup(Game *game)
{
    if (game->powerup->position->x < game->player->position->x + game->player->size &&
        game->powerup->position->x + SIZE_POWER_UP > game->player->position->x &&
        game->powerup->position->y < game->player->position->y + game->player->size &&
        game->powerup->position->y + SIZE_POWER_UP > game->player->position->y)
    {
        return 1;
    }
    return 0;
}
void player_get_powerup(Game *game)
{
    if (touch_powerup(game))
    {
        game->powerup->in_the_game = 0;
        game->player->has_powerup = 1;
        free(game->powerup->position);
        game->powerup->position = NULL;
        game->player->powerup->type = game->powerup->type;
        game->player->powerup->animation = 10000;
    }
}
void move_powerup(Game *game)
{
    if (game->powerup->position->x < 0 - SIZE_POWER_UP)
    {
        game->powerup->in_the_game = 0;
        free(game->powerup->position);
    }
    else
    {
        game->powerup->position->x -= game->powerup->speed;
        player_get_powerup(game);
    }
}
