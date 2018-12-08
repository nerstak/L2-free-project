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
    Isaac->stats = malloc(sizeof(generalStats));
    if(!Isaac->stats) {
        printf("Fail to init general stats of the player.");
        exit(EXIT_FAILURE);
    }
    
    Isaac->stats->current = malloc(sizeof(stats_entity));
    Isaac->stats->basic = malloc(sizeof(stats_entity));
    Isaac->stats->max = malloc(sizeof(stats_entity));
    Isaac->stats->potionsUsed = calloc(6,sizeof(int));
    if(!Isaac->stats->max || !Isaac->stats->basic || !Isaac->stats->current || !Isaac->stats->potionsUsed) {
        printf("Fail to init stats of the player.");
        exit(EXIT_FAILURE);
    }

    Isaac->weapons = malloc(sizeof(Weapon )* 4);
    if(!Isaac->weapons) {
        printf("Fail to init Player weapons'.");
        exit(EXIT_FAILURE);
    }

    Isaac->gameStats = malloc(sizeof(GameStats));
    if(!Isaac->gameStats) {
        printf("Fail to init GameStats'.");
        exit(EXIT_FAILURE);
    }

    Isaac->invulframes= init_Timer();
    if(!Isaac->invulframes) {
        printf("Fail to init Invulnity frames'.");
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

    Isaac->movement->Hitbox = malloc(sizeof(SDL_Rect));
    if(!Isaac->movement->Hitbox) {
        printf("Fail to init HitBox of player.");
        exit(EXIT_FAILURE);
    }

    Isaac->movement->Hitbox->h = 64;
    Isaac->movement->Hitbox->w = 64;

    Isaac->movement->timesince=init_Timer();
    if(!Isaac->movement->timesince) {
        printf("Fail to init movement timer of player.");
        exit(EXIT_FAILURE);
    }

    Isaac->movement->step = 0;
    Isaac->movement->direction = 0;


    Isaac->combat=malloc(sizeof(CombatValues));
    if(!Isaac->combat) {
        printf("Fail to init combat of player.");
        exit(EXIT_FAILURE);
    }


    Isaac->combat->SpriteBox=malloc(sizeof(SDL_Rect));
    if(!Isaac->combat) {
        printf("Fail to init combat SpriteBox of player.");
        exit(EXIT_FAILURE);
    }

    Isaac->combat->WeaponHitbox=malloc(sizeof(SDL_Rect));
    if(!Isaac->combat) {
        printf("Fail to init combat WeaponHitBox of player.");
        exit(EXIT_FAILURE);
    }

    Isaac->combat->timesince=init_Timer();
    if(!Isaac->combat->timesince){
        printf("Fail to init combat timer of player.");
        exit(EXIT_FAILURE);
    }

    Isaac->combat->direction=-1;
    Isaac->combat->step=0;


    return Isaac;
}

extern void freePlayer(Player** Isaac) {
    if((*Isaac)->movement) {
        if((*Isaac)->movement->SpriteBox) {
            free((*Isaac)->movement->SpriteBox);
            (*Isaac)->movement->SpriteBox = NULL;
        }

        if((*Isaac)->movement->velocity) {
            free((*Isaac)->movement->velocity);
            (*Isaac)->movement->velocity = NULL;
        }

        if((*Isaac)->movement->pos) {
            free((*Isaac)->movement->pos);
            (*Isaac)->movement->pos = NULL;
        }

        free((*Isaac)->movement);
        (*Isaac)->movement = NULL;
    }

    if((*Isaac)->weapons) {
        free((*Isaac)->weapons);
        (*Isaac)->weapons = NULL;
    }

    if((*Isaac)->stats) {
        if((*Isaac)->stats->max) {
            free((*Isaac)->stats->max);
            (*Isaac)->stats->max = NULL;
        }

        if((*Isaac)->stats->current) {
            free((*Isaac)->stats->current);
            (*Isaac)->stats->current = NULL;
        }

        if((*Isaac)->stats->basic) {
            free((*Isaac)->stats->basic);
            (*Isaac)->stats->basic = NULL;
        }

        if((*Isaac)->stats->potionsUsed) {
            free((*Isaac)->stats->potionsUsed);
            (*Isaac)->stats->potionsUsed = NULL;
        }

        free((*Isaac)->stats);
        (*Isaac)->stats = NULL;        
    }
    
    

    if((*Isaac)->gameStats) {
        free((*Isaac)->gameStats);
        (*Isaac)->gameStats = NULL;
    }

    freeAll_SlotInventory(&((*Isaac)->inventory));

    free(*Isaac);
    *Isaac = NULL;
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
            Isaac->stats->current->health = (alterHealth + Isaac->stats->current->health);

            if(Isaac->stats->current->health > Isaac->stats->basic->health) {
                Isaac->stats->current->health = Isaac->stats->basic->health;
            }
            if (Isaac->stats->current->health <= 0) {
                Isaac->stats->current->health = 0;
            }
            break;
        }
        case 'b': {
            Isaac->stats->basic->health = (alterHealth + Isaac->stats->basic->health);

            if(Isaac->stats->basic->health > Isaac->stats->max->health) {
                Isaac->stats->basic->health = Isaac->stats->max->health;
            }
            if (Isaac->stats->basic->health <= 0) {
                Isaac->stats->basic->health = 0;
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
            Isaac->stats->current->speed = (alterSpeed + Isaac->stats->current->speed);

            if(Isaac->stats->current->speed > Isaac->stats->max->speed) {
                Isaac->stats->current->speed = Isaac->stats->max->speed;
            }
            if (Isaac->stats->current->speed <= 0) {
                Isaac->stats->current->speed = 0;
            }
            break;
        }
        case 'b': {
            Isaac->stats->basic->speed = (alterSpeed + Isaac->stats->basic->speed);

            if(Isaac->stats->basic->speed > Isaac->stats->max->speed) {
                    Isaac->stats->basic->speed = Isaac->stats->max->speed;
            }
            if (Isaac->stats->basic->speed <= 0) {
                Isaac->stats->basic->speed = 0;
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
            Isaac->stats->current->agility = (alterAgility + Isaac->stats->current->agility);

            if(Isaac->stats->current->agility > Isaac->stats->max->agility) {
                    Isaac->stats->current->agility = Isaac->stats->max->agility;
                }
            if (Isaac->stats->current->agility <= 0) {
                Isaac->stats->current->agility = 0;
            }
            break;
        }
        case 'b': {
            Isaac->stats->basic->agility = (alterAgility + Isaac->stats->basic->agility);

            if(Isaac->stats->basic->agility > Isaac->stats->max->agility) {
                Isaac->stats->basic->agility = Isaac->stats->max->agility;
            }
            if (Isaac->stats->basic->agility <= 0) {
                Isaac->stats->basic->agility = 0;
            }
        }
        default: break;
    }
}

//Change the damage of the Player. 'b' for definitif, 'c' for temp
extern void alterDamage(Player* Isaac, float alterDamage, char type) {
    switch(type) {
        case 'c': {
            Isaac->stats->current->damage = (alterDamage + Isaac->stats->current->damage);

            if(Isaac->stats->current->damage > Isaac->stats->max->damage) {
                Isaac->stats->current->damage = Isaac->stats->max->damage;
            }
            if (Isaac->stats->current->damage <= 0) {
                Isaac->stats->current->damage = 0;
            }
            break;
        }
        case 'b': {
            Isaac->stats->basic->damage = (alterDamage + Isaac->stats->basic->damage);

            if(Isaac->stats->basic->damage > Isaac->stats->max->damage) {
                Isaac->stats->basic->damage = Isaac->stats->max->damage;
            }
            if (Isaac->stats->basic->damage <= 0) {
                Isaac->stats->basic->damage = 0;
            }
        }
        default: break;
    }
}
