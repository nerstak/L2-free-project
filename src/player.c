#include <stdlib.h>
#include <string.h>

#include "player.h"

extern Player* initPlayer() {
    Player* Isaac = malloc(sizeof(Player));
    if(!Isaac) {
        printf("Fail to init player.");
        exit(EXIT_FAILURE);
    }
    Isaac->inventory = NULL;

    //Initialisation of stats
    Isaac->current_stats = malloc(sizeof(stats_entity));
    Isaac->basic_stats = malloc(sizeof(stats_entity));
    Isaac->maxStats = malloc(sizeof(stats_entity));
    if(!Isaac->current_stats || !Isaac->basic_stats || !Isaac->maxStats) {
        printf("Fail to init stats of the player.");
        exit(EXIT_FAILURE);
    }

    Isaac->weapons = malloc(sizeof(Weapon )* 4);
    if(!Isaac->weapons) {
        printf("Fail to init Player weapons'.");
        exit(EXIT_FAILURE);
    }

    //Initialisation of coordinates and movement
    //Those coordinates will have to correspond to the one of the lobby
    Isaac->movement = malloc(sizeof(MovementValues));
    if(!Isaac->movement) {
        printf("Fail to init movement of player.");
        exit(EXIT_FAILURE);
    }

    Isaac->movement->pos = malloc(sizeof(coordinates_entity));
    if(!Isaac->movement->pos) {
        printf("Fail to init pos of player.");
        exit(EXIT_FAILURE);
    }
    Isaac->movement->pos->x = 640;
    Isaac->movement->pos->y = 400;

    Isaac->movement->velocity = malloc(sizeof(coordinates_entity));
    if(!Isaac->movement->velocity) {
        printf("Fail to init velocity of player.");
        exit(EXIT_FAILURE);
    }
    Isaac->movement->velocity->x = 0;
    Isaac->movement->velocity->y = 0;

    Isaac->movement->SpriteBox = malloc(sizeof(SDL_Rect));
    if(!Isaac->movement->SpriteBox) {
        printf("Fail to init SpriteBox of player.");
        exit(EXIT_FAILURE);
    }
    Isaac->movement->SpriteBox->x = 0;
    Isaac->movement->SpriteBox->y = 0;
    Isaac->movement->SpriteBox->h = 128;
    Isaac->movement->SpriteBox->w = 64;

    Isaac->movement->step = 0;
    Isaac->movement->direction = 0;

    return Isaac;
}

extern void freePlayer(Player** Isaac) {
    free((*Isaac)->movement->SpriteBox);
    (*Isaac)->movement->SpriteBox = NULL;

    free((*Isaac)->movement->velocity);
    (*Isaac)->movement->velocity = NULL;

    free((*Isaac)->movement->pos);
    (*Isaac)->movement->pos = NULL;

    free((*Isaac)->movement);
    (*Isaac)->movement = NULL;

    free((*Isaac)->weapons);
    (*Isaac)->weapons = NULL;

    free((*Isaac)->maxStats);
    (*Isaac)->maxStats = NULL;

    free((*Isaac)->current_stats);
    (*Isaac)->current_stats = NULL;

    free((*Isaac)->basic_stats);
    (*Isaac)->basic_stats = NULL;

    freeAll_SlotInventory(&((*Isaac)->inventory));
}

//Change the balance of the wallet, IFF possible (return 1 if done)
extern int alterMoney(Player* Isaac, int alterMoney) {
    if (Isaac->money + alterMoney >= 0 && Isaac->money + alterMoney <= 15000) {
        Isaac->money = Isaac->money + alterMoney;
        return 1;
    }
    return 0;
}

//Change the health of the Player. 'b' for definitif, 'c' for temp
extern void alterHealth(Player* Isaac, float alterHealth, char type) {
    switch(type) {
        case 'c': {
            Isaac->current_stats->health = (alterHealth + Isaac->current_stats->health);

            if(Isaac->current_stats->health > Isaac->basic_stats->health) {
                Isaac->current_stats->health = Isaac->basic_stats->health;
            }
            if (Isaac->current_stats->health <= 0) {
                Isaac->current_stats->health = 0;
            }
            break;
        }
        case 'b': {
            Isaac->basic_stats->health = (alterHealth + Isaac->basic_stats->health);

            if(Isaac->basic_stats->health > Isaac->maxStats->health) {
                Isaac->basic_stats->health = Isaac->maxStats->health;
            }
            if (Isaac->basic_stats->health <= 0) {
                Isaac->basic_stats->health = 0;
            }
            break;
        }
        default: break;
    }
}

//Change the speed of the Player. 'b' for definitif, 'c' for temp
extern void alterSpeed(Player* Isaac, float alterSpeed, char type) {
    switch(type) {
        case 'c': {
            Isaac->current_stats->speed = (alterSpeed + Isaac->current_stats->speed);

            if(Isaac->current_stats->speed > Isaac->basic_stats->speed) {
                Isaac->current_stats->speed = Isaac->basic_stats->speed;
            }
            if (Isaac->current_stats->speed <= 0) {
                Isaac->current_stats->speed = 0;
            }
            break;
        }
        case 'b': {
            Isaac->basic_stats->speed = (alterSpeed + Isaac->basic_stats->speed);

            if(Isaac->basic_stats->speed > Isaac->maxStats->speed) {
                    Isaac->basic_stats->speed = Isaac->maxStats->speed;
            }
            if (Isaac->basic_stats->speed <= 0) {
                Isaac->basic_stats->speed = 0;
            }
            break;
        }
        default: break;
    }
}

//Change the agility of the Player. 'b' for definitif, 'c' for temp
extern void alterAgility(Player* Isaac, float alterAgility, char type) {
    switch(type) {
        case 'c': {
            Isaac->current_stats->agility = (alterAgility + Isaac->current_stats->agility);

            if(Isaac->current_stats->agility > Isaac->basic_stats->agility) {
                    Isaac->current_stats->agility = Isaac->basic_stats->agility;
                }
            if (Isaac->current_stats->agility <= 0) {
                Isaac->current_stats->agility = 0;
            }
            break;
        }
        case 'b': {
            Isaac->basic_stats->agility = (alterAgility + Isaac->basic_stats->agility);

            if(Isaac->basic_stats->agility > Isaac->maxStats->agility) {
                Isaac->basic_stats->agility = Isaac->maxStats->agility;
            }
            if (Isaac->basic_stats->agility <= 0) {
                Isaac->basic_stats->agility = 0;
            }
        }
        default: break;
    }
}

//Change the damage of the Player. 'b' for definitif, 'c' for temp
extern void alterDamage(Player* Isaac, float alterDamage, char type) {
    switch(type) {
        case 'c': {
            Isaac->current_stats->damage = (alterDamage + Isaac->current_stats->damage);

            if(Isaac->current_stats->damage > Isaac->basic_stats->damage) {
                Isaac->current_stats->damage = Isaac->basic_stats->damage;
            }
            if (Isaac->current_stats->damage <= 0) {
                Isaac->current_stats->damage = 0;
            }
            break;
        }
        case 'b': {
            Isaac->basic_stats->damage = (alterDamage + Isaac->basic_stats->damage);

            if(Isaac->basic_stats->damage > Isaac->maxStats->damage) {
                Isaac->basic_stats->damage = Isaac->maxStats->damage;
            }
            if (Isaac->basic_stats->damage <= 0) {
                Isaac->basic_stats->damage = 0;
            }
        }
        default: break;
    }
}