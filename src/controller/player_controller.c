#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/const.h"
#include "../include/struct_entity.h"
#include "../include/window.h"

Player *init_player()
{

    Player *player = malloc(sizeof(Player));
    assert(player != NULL);

    player->size = SIZE_PLAYER;
    Position *position = malloc(sizeof(Position));
    assert(position != NULL);
    position->x = (player->size);
    position->y = HEIGHT_FRAME / 2 - player->size / 2;
    player->position = position;

    player->health = 5;

    player->speed = 0;
    player->score = 0;

    Hitbox *hitbox = malloc(sizeof(Hitbox));
    assert(hitbox != NULL);
    hitbox->position = player->position;
    hitbox->size = player->size / 2;
    player->hitbox = hitbox;

    Powerup *powerup = malloc(sizeof(Powerup));
    assert(powerup != NULL);
    player->powerup = powerup;

    return player;
}

void move_player_left(Player *player)
{
    if (player->position->x > 0)
    {
        player->position->x = player->position->x - player->speed;
    }
}

void move_player_right(Player *player)
{
    if (player->position->x < WIDTH_FRAME - player->size)
    {
        player->position->x = player->position->x + player->speed;
    }
}
void move_player_up(Player *player)
{
    if (player->position->y > PADDING_TOP)
    {
        player->position->y = player->position->y - player->speed;
    }
}
void move_player_down(Player *player)
{
    if (player->position->y < HEIGHT_FRAME - player->size / 1.1)
    {
        player->position->y = player->position->y + player->speed;
    }
}

void active_power_up(Game *game)
{

    switch (game->player->powerup->type)
    {
    case 1:
        game->player->powerup->animation = 180;
        game->player->powerup->is_actif = 1;

        draw_power_up_dbz(game);
        break;
    case 2:
        game->player->powerup->animation = 0;
        game->player->powerup->is_actif = 0;
        game->player->powerup->type = 0;

        if(game->player->health < 5)
        {
            game->player->health += 1;
        }
        
        break;
    case 3:
        game->player->powerup->animation = 180;
        game->player->powerup->is_actif = 1;
        game->player->powerup->type = 3;
        game->player->speed = 80;
        break;
    default:
        break;
    }

    game->player->has_powerup = 0;
}

int player_is_dead(Game *game)
{
    if (game->player->health <= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
