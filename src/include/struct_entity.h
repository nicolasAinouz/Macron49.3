#ifndef __STRUCTENTITY__
#define __STRUCTENTITY__

#include "MLV/MLV_all.h"

typedef struct position
{
    int x;
    int y;
} Position;

typedef struct hitbox
{
    Position *position;
    int size;
} Hitbox;
typedef struct powerup
{
    int is_actif;
    int type;
    int animation;
    int in_the_game;
    int speed;
    Position *position;
} Powerup;

typedef struct player
{
    Position *position;
    int size;
    int health;
    int speed;
    int score;
    int has_powerup;
    Powerup *powerup;
    int shoot;
    int is_shooting_too_much;

    Hitbox *hitbox;
} Player;

typedef struct rocket
{
    Position *position;
    int size;
    int speed;
    int damage;
    int is_alive;
    Hitbox *hitbox;
    int is_player;      // 1 si tiré par le joueur
    int is_special;     // 1 si spécial
    int time;           // temps de vie (que pour special)
    int time_explosion; // temps d'explosion (que pour special)
} Rocket;

typedef struct enemy
{
    Position *position;
    int size;
    int health;
    int time; //for special
    int speed;
    int is_alive;   // est en vie si = 1
    int is_special; // est spécial si = 1
    Hitbox *hitbox;
} Enemy;

typedef struct image_game
{
    MLV_Image *img_rocket;
    MLV_Image *img_enemy_tank;
    MLV_Image *img_player;
    MLV_Image *img_background;
    MLV_Image *img_explosion;
    MLV_Image *img_bullet_tank;
    MLV_Image *img_enemy;
    MLV_Image *img_bullet_player;

    MLV_Image *img_powerup_dbz;
    MLV_Image *img_player_dbz;
    MLV_Image *img_explosion_dbz;

    MLV_Image *img_powerup_health;

    MLV_Image *img_powerup_speed;
} Image_Game;

typedef struct game
{
    Enemy *tab_enemy[NUMBER_OF_ENEMY];
    Rocket *tab_rocket[NUMBER_OF_ROCKET];
    Player *player;
    int scale;
    int number_enemies_key;
    int number_rocket_key;
    int end_game;
    int last_keyboard_push;
    int has_powerup;
    double difficulty;
    Image_Game *image;
    Powerup *powerup;
    MLV_Sound *sounddbz;
    MLV_Font *font;

} Game;

#endif